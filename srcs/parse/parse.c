/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:25:02 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/06 18:31:35 by jmontija         ###   ########.fr       */
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

void		ft_create_parse(t_group *grp, char *cmd)
{
	t_parse		*tmp;
	t_parse		*tmp2;

	tmp = (t_parse*)malloc(sizeof(t_parse));
	tmp->cmd = ft_strtrim(cmd);
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
	//spacesplit bug
	tmp->cmdsplit = ft_strsplit(tmp->cmd, ' ');
	if (!grp->parselst)
		grp->parselst = tmp;
	else
	{
		tmp2 = grp->parselst;
		while (tmp2 && tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

void		ft_parse2(t_group *grp)
{
	t_parse		*tmp;
	int			i;

	tmp = grp->parselst;
	while (tmp)
	{
		i = ft_strlen(tmp->cmd);
		while (i > 0 && tmp->cmd && tmp->cmd[--i] == ' ')
			tmp->cmd[i] = '\0';
		tmp = tmp->next;
	}
}

void		ft_parse(t_group *grp, char *cmd)
{
	char		**tabl;
	int			i;
	int			y;

	i = -1;
	tabl = ft_strsplitquote(cmd, '|');
	y = ft_count_pipes(cmd);
	while (tabl && tabl[++i])
	{
		ft_create_parse(grp, tabl[i]);
		ft_strdel(&tabl[i]);
	}
	if (tabl)
		free(tabl);
	TERM(cmd_size) = 0;
	cmd = NULL;
	if (y != i)
	{
		grp->fail = 1;
		return (ft_putendl("Invalid null command"));
	}
	ft_parse2(grp);
	check_heredoc(grp);
}
