/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:25:02 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 13:04:16 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_count_pipes(char *cmd)
{
	int i;
	int nb;

	nb = 1;
	i = -1;
	while (cmd && cmd[++i])
		if (cmd[i] == '|')
			nb++;
	return (nb);
}

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
	while (parse->cmd[++i])
	{
		ret = check_parentheses(parse->cmd[i]);
		if (test == 0 && ret == 1)
		{
			test = 1;
			printf("%c\n", parse->cmd[i]);
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
	while (ft_is_space(cmd[0]) && cmd[1])
		cmd = &cmd[1];
	tmp->cmd = ft_strdup(cmd);
	tmp->next = NULL;
	tmp->heredoc = 0;
	tmp->dbred = NULL;
	tmp->sgred = NULL;
	tmp->file = NULL;
	tmp->closefd = 0;
	tmp->errnb = 0;
	ft_parse_redirections(grp, tmp);
	polish(tmp);
	tmp->cmdsplit = ft_spacesplit(tmp->cmd);
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
	if (y != i)
	{
		grp->fail = 1;
		return (ft_putendl("Invalid null command"));
	}
	TERM(cmd_size) = 0;
	cmd = NULL;
	ft_parse2(grp);
}
