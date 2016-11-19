/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:14:56 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/19 21:43:50 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** parsing for heredoc
** format char**
*/

void		ft_addheredoc(t_group *grp, t_parse *parse, int i)
{
	char	*tmp;

	tmp = get_redirection(grp, parse, i,  i - 2);
	if (!parse->heredoc)
	{
		parse->heredoc = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		parse->heredoc = ft_strjoin_nf(parse->heredoc,
		ft_strjoin_nf(";", tmp, 2), 3);
	if (parse->file)
		REMOVE(&parse->file);
}

/*
** parsing for closing fd
** format char** separated by ';'
*/

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

/*
** parsing for redirection fd
** format char** "'(int)out'>'(int)in'"
*/


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
