/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 21:55:58 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/22 20:48:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_replace_dollar(t_group *grp, t_parse *parse, char *tmp2,
	int start)
{
	parse->cmd[start - 1] = '\0';
	if (!parse->cmd[start + 1])
		parse->cmd = ft_strjoin_nf(parse->cmd, ft_itoa(grp->exit), 3);
	else
		parse->cmd = JOINF(JOINF(parse->cmd, ft_itoa(grp->exit), 3), tmp2, 1);
}

/*
** replacing environment variables in parse cmd
*/

void		ft_replace_vars(t_group *grp, t_parse *parse, int i)
{
	int		start;
	char	*tmp;
	char	*tmp2;

	start = i;
	while (parse->cmd[i] && (ft_isalpha(parse->cmd[i]) || parse->cmd[i] == '?'))
		i++;
	tmp = ft_strsub(&parse->cmd[start], 0, i - start);
	tmp2 = ft_strdup(&parse->cmd[i]);
	if (ft_strlen(tmp) == 1 && tmp[0] == '?')
		ft_replace_dollar(grp, parse, tmp2, start);
	else if (ft_getenv(grp, tmp) == NULL)
		grp->minus = 1;
	else
	{
		parse->cmd[start - 1] = '\0';
		if (!parse->cmd[start + 1])
			parse->cmd = ft_strjoin_nf(parse->cmd, ft_getenv(grp, tmp), 1);
		else
			parse->cmd = JOINF(JOINF(parse->cmd,
			ft_getenv(grp, tmp), 1), tmp2, 1);
		ft_strdel(&tmp2);
	}
	(tmp) ? REMOVE(&tmp) : 0;
	(tmp2) ? REMOVE(&tmp2) : 0;
}

/*
** creating files for redirections
*/

void		ft_create_redirections(t_parse *parse)
{
	if (parse->sgred)
		parse->fd = open(parse->sgred, O_WRONLY |
		O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (parse->dbred)
		parse->fd = open(parse->dbred, O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
}

/*
** replacing tilde in parse cmd
*/

void		ft_replace_tilde(t_group *grp, t_parse *parse, int i)
{
	char	*path;
	char	*tmp;

	path = ft_getenv(grp, "HOME");
	if (path == NULL)
		ft_putendl_fd("Your stupid theres no home", 2);
	tmp = SDUP(&parse->cmd[i + 1]);
	parse->cmd[i] = '\0';
	if (parse->cmd[i + 1])
	{
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
	}
	else
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
	REMOVE(&tmp);
	grp->minus = 1;
}

/*
** replacing backquotes in parse cmd
*/

void		ft_replace_bquote(t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*bquote;
	char	*begin;

	start = i + 1;
	i = start;
	end = 0;
	while (parse->cmd[i] != '`')
	{
		end++;
		i++;
	}
	bquote = SUB(parse->cmd, start, end);
	if (parse->bquotes != NULL)
		parse->bquotes = JOINF(JOINF(parse->bquotes, ";", 1), bquote, 2);
	else
	{
		parse->bquotes = SDUP(bquote);
		REMOVE(&bquote);
	}
	begin = SUB(parse->cmd, 0, start - 1);
	parse->cmd = JOINF(begin, SUB(parse->cmd, start + end + 1,
	LEN(parse->cmd)), 2);
	check_parentheses(0);
}
