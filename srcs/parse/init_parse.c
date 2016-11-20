/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:59:55 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/20 20:40:18 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** init values of parse node
*/

static void		ft_parsenode_init(t_parse *tmp)
{
	tmp->next = NULL;
	tmp->heredoc = 0;
	tmp->dbred = NULL;
	tmp->sgred = NULL;
	tmp->file = NULL;
	tmp->redfd = NULL;
	tmp->closefd = NULL;
	tmp->bquotes = NULL;
	tmp->errnb = 0;
	tmp->fd = -1;
	tmp->fail = 0;
}

/*
** creates new parse node
*/

static void		ft_create_parse(t_group *grp, t_andor *tabl, t_andor *andor)
{
	t_parse		*tmp;
	t_parse		*tmp2;

	tmp = (t_parse*)malloc(sizeof(t_parse));
	tmp->cmd = ft_strtrim(tabl->cmd);
	ft_parsenode_init(tmp);
	ft_parse_redirections(grp, tmp);
	polish(tmp);
	tmp->cmdsplit = ft_strsplit(tmp->cmd, ' ');
	if (!andor->parselst)
		andor->parselst = tmp;
	else
	{
		tmp2 = andor->parselst;
		while (tmp2 && tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

/*
** spliting on andor node and creating parses nodes
*/

static int		ft_parse(t_group *grp, t_andor *andor)
{
	t_andor		*tabl;
	t_andor		*tmp;
	int			i;

	i = 0;
	tabl = ft_strsplitpipe(andor->cmd, '|');
	while (tabl)
	{
		if (tabl->cmd[0] == '\0' && !grp->fail) 
		{
			grp->fail = 1;
			error_cmd("Invalid null command near", "|", 1);
			return (-1) ;
		}
		ft_create_parse(grp, tabl, andor);
		REMOVE(&tabl->cmd);
		tmp = tabl->next;
		free(tabl);
		tabl = tmp;
		i++;
	}
	TERM(cmd_size) = 0;
	return (0);
}

/*
** spliting on allcmd nodes and creating andor nodes
*/

void			ft_init_parse(t_group *grp)
{
	t_allcmd	*tabl;
	t_andor		*tmp2;

	tabl = grp->allcmd;
	while (tabl)
	{
		tabl->andor = ft_strsplitandor(tabl->cmd);
		tmp2 = tabl->andor;
		while (tmp2)
		{
			if (tmp2->cmd[0] == '\0' && !grp->fail)
			{
				grp->fail = 1;
				error_cmd("Invalid null command near", "separator (&& / ||)", 1);
				return ;
			}
			if (ft_parse(grp, tmp2) < 0)
				return ;
			tmp2 = tmp2->next;
		}
		tabl = tabl->next;
	}
	check_heredoc(grp);
}
