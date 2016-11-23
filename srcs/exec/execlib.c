/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 22:45:03 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/23 22:48:00 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			check_cmd(char **path, char *cmd)
{
	struct stat	s_buf;
	mode_t		val;
	int			ret;

	if (*path == NULL)
		*path = SDUP(cmd);
	ret = lstat(*path, &s_buf);
	val = (s_buf.st_mode & ~S_IFMT);
	if (ret != 0)
		error_cmd("command not found", cmd, 1);
	else if (s_buf.st_size <= 0)
		error_cmd("executable format error", cmd, 1);
	else if (!(val & S_IXUSR) || S_ISDIR(s_buf.st_mode))
		error_cmd("Permission denied", cmd, 1);
	else
		return (0);
	return (-1);
}

void		ft_dup_redirection(t_parse *parse)
{
	char	**tmp;
	int		i;

	if (parse->redfd)
	{
		tmp = ft_strsplit(parse->redfd, '>');
		parse->fd = dup2(ft_atoi(tmp[1]), ft_atoi(tmp[0]));
		REMOVE(&tmp[0]);
		REMOVE(&tmp[1]);
		free(tmp);
	}
	if (parse->closefd)
	{
		tmp = ft_strsplit(parse->closefd, ';');
		i = -1;
		while (tmp[++i])
		{
			close(ft_atoi(tmp[i]));
			REMOVE(&tmp[i]);
		}
		free(tmp);
	}
}