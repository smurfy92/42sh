/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:26:28 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 15:46:12 by jmontija         ###   ########.fr       */
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
** replacing backquotes in parse cmd
*/

char		*replace_bquote(t_group *grp, char *bquote)
{
	int		fd;
	char	*bquote_result;
	char	*line;

	line = NULL;
	exec_bquotes(grp, bquote);
	fd = open("/tmp/.fromshell", O_RDONLY);
	bquote_result = NEW(0);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_charjoin(line, ' ');
		bquote_result = JOINF(bquote_result, line, 3);
	}
	close(fd);
	bquote_result[LEN(bquote_result) - 1] = '\0';
	return (bquote_result);
}

void		ft_replace_bquote(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*bquote;
	char	*begin;
	char	*tmp;

	start = i + 1;
	i = start;
	end = 0;
	while (parse->cmd[i] != '`')
	{
		end++;
		i++;
	}
	bquote = SUB(parse->cmd, start, end);
	tmp = SDUP(bquote);
	REMOVE(&bquote);
	bquote = replace_bquote(grp, tmp);
	REMOVE(&tmp);
	begin = JOINF(SUB(parse->cmd, 0, start - 1), bquote, 3);
	parse->cmd = JOINF(begin, SUB(parse->cmd, start + end + 1,
	LEN(parse->cmd)), 2);
	REMOVE(&begin);
	check_parentheses(0);
}
