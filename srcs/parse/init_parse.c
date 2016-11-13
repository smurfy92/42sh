/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:59:55 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 01:21:18 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_polish_parse(t_parse *parse, int i)
{
	char	*tmp;

	if (parse->cmd[i + 2])
	{
		tmp = SDUP(&parse->cmd[i + 2]);
		parse->cmd[i + 1] = '\0';
		parse->cmd = JOINF(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i + 1] = '\0';
}

static void		polish(t_parse *parse)
{
	int ret;
	int test;
	int i;

	test = 0;
	i = -1;
	check_parentheses(0);
	while (parse->cmd[++i])
	{
		ret = check_parentheses(parse->cmd[i]);
		if (parse->cmd[i] == '\\' &&
			parse->cmd[i + 1])
			ft_polish_parse(parse, i - 1);
		if (test == 0 && ret == 1)
		{
			test = 1;
			ft_polish_parse(parse, i - 1);
		}
		else if (test == 1 && ret == 0)
		{
			test = 0;
			ft_polish_parse(parse, i - 1);
		}
	}
}

static void		ft_create_parse(t_group *grp, t_andor *tabl, t_andor *andor)
{
	t_parse		*tmp;
	t_parse		*tmp2;

	tmp = (t_parse*)malloc(sizeof(t_parse));
	tmp->cmd = ft_strtrim(tabl->cmd);
	tmp->next = NULL;
	tmp->heredoc = 0;
	tmp->dbred = NULL;
	tmp->sgred = NULL;
	tmp->file = NULL;
	tmp->redfd = NULL;
	tmp->closefd = NULL;
	tmp->errnb = 0;
	tmp->fd = -1;
	tmp->fail = 0;
	ft_parse_redirections(grp, tmp);
	polish(tmp);
	tmp->cmdsplit = ft_strsplit(tmp->cmd, ' '); // don't forget tab ! 	//spacesplit a update !
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

static void		ft_parse(t_group *grp, t_andor *andor)
{
	t_andor		*tabl;
	t_andor		*tmp;
	int			i;
	int			y;

	i = 0;
	tabl = ft_strsplitpipe(andor->cmd, '|');
	y = ft_count_pipes(andor->cmd);
	while (tabl)
	{
		if (tabl->cmd[0] == '\0' && !grp->fail)
		{
			grp->fail = 1;
			ft_putendl("Invalid null command.");
		}
		if (!grp->fail)
			ft_create_parse(grp, tabl, andor);
		REMOVE(&tabl->cmd);
		tmp = tabl->next;
		free(tabl);
		tabl = tmp;
		i++;
	}
	TERM(cmd_size) = 0;
	check_heredoc(grp);
}

void		ft_init_parse(t_group *grp)
{
	t_allcmd *tabl;
	t_andor *tmp2;

	tabl = grp->allcmd;
	while (tabl)
	{
		tabl->andor = ft_strsplitandor(tabl->cmd);
		tmp2 = tabl->andor;
		while (tmp2)
		{
			ft_parse(grp, tmp2);
			tmp2 = tmp2->next;
		}
		tabl = tabl->next;
	}
}
