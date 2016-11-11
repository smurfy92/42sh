/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:14:56 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/11 16:16:18 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_addheredoc2(t_parse *parse, int end, int start)
{
	char	*tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
}

void		ft_addheredoc(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*tmp;

	start = i - 2;
	int test = check_parentheses(parse->cmd[i]);
	while (!ft_isalpha(parse->cmd[i]) && parse->cmd[i])
		i++;
	end = i;
	while ((parse->cmd[end] && !ft_end_of_red(parse->cmd[end]) &&
	!ft_is_quote(parse->cmd[i])) ||
	(test == 0 && check_parentheses(parse->cmd[end])))
		end++;
	if (end == i)
	{
		grp->fail = 1;
		return (ft_putendl_fd("42sh: parse error near `\\n'", 2));
	}
	tmp = ft_strsub(&parse->cmd[i], 0, end - i);
	if (!parse->heredoc)
	{
		parse->heredoc = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		parse->heredoc = ft_strjoin_nf(parse->heredoc,
		ft_strjoin_nf(";", tmp, 2), 3);
	ft_addheredoc2(parse, end, start);
}

void		ft_addfile(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*tmp;

	start = i - 1;
	while (!ft_isalpha(parse->cmd[i]) && parse->cmd[i] &&
	!ft_is_quote(parse->cmd[i]) && parse->cmd[i] != '/')
		i++;
	end = i;
	while (parse->cmd[end] && !ft_end_of_red(parse->cmd[end]))
		end++;
	if (end == i)
	{
		grp->fail = 1;
		return (ft_putendl_fd("jush : parse error near `\\n'", 2));
	}
	tmp = ft_strsub(&parse->cmd[i], 0, end - i);
	parse->file = ft_strdup(tmp);
	parse->sgred = NULL;
	parse->dbred = NULL;
	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin(parse->cmd, tmp);
}

void		ft_check_close(t_parse *parse, int i)
{
	char	*tmp;
	char	*fd;

	fd = ft_strsub(parse->cmd, i, 1);
	if (parse->cmd[i + 4])
	{
		tmp = ft_strdup(&parse->cmd[i + 4]);
		parse->cmd[i] = '\0';
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i] = '\0';
	if (parse->closefd)
	{
		parse->closefd = ft_strjoin_nf(parse->closefd, ";", 1);
		parse->closefd = ft_strjoin_nf(parse->closefd, fd, 1);
	}
	else
		parse->closefd = ft_strdup(fd);
	REMOVE(&fd);
}

void		ft_check_redirection_fd(t_parse *parse, int i)
{
	char	*tmp;
	char	*fd;
	char	*fd2;

	fd2 = ft_strsub(parse->cmd, i + 3, 1);
	fd = ft_strsub(parse->cmd, i, 1);
	if (parse->cmd[i + 4])
	{
		tmp = ft_strdup(&parse->cmd[i + 4]);
		parse->cmd[i] = '\0';
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i] = '\0';
	fd = ft_strjoin_nf(fd, ">", 1);
	fd = ft_strjoin_nf(fd, fd2, 3);
	if (parse->redfd)
		REMOVE(&parse->redfd);
	parse->redfd = ft_strdup(fd);
	REMOVE(&fd);
}
