/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:25:02 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/09 19:44:50 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_polish_parse(t_parse *parse, int i)
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

void		polish(t_parse *parse)
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

void		ft_create_parse(t_group *grp, t_andor *tabl, t_andor *andor)
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
	ft_parse_redirections(grp, tmp);
	polish(tmp);
	tmp->cmdsplit = ft_strsplit(tmp->cmd, ' '); // don't forget tab ! 	//spacesplit a update !
	if (!andor->parselst)
	{
		andor->parselst = tmp;
	}
	else
	{
		tmp2 = andor->parselst;
		while (tmp2 && tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

void		ft_parse2(t_andor *andor)
{
	t_parse		*tmp;
	int			i;

	tmp = andor->parselst;
	while (tmp)
	{
		i = ft_strlen(tmp->cmd);
		while (i > 0 && tmp->cmd && tmp->cmd[--i] == ' ')
			tmp->cmd[i] = '\0';
		tmp = tmp->next;
	}
}

void		ft_parse(t_group *grp, t_andor *andor)
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
		ft_create_parse(grp, tabl, andor);
		REMOVE(&tabl->cmd);
		tmp = tabl->next;
		free(tabl);
		tabl = tmp;
		i++;
	}
	TERM(cmd_size) = 0;
	if (y != i)
	{
		grp->fail = 1;
		return (ft_putendl("Invalid null command."));
	}
	ft_parse2(andor);
	//check_heredoc(grp);
}
