/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:48:45 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/22 20:59:52 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	cderr_pwd(t_group *grp, char **path, struct stat s_buf, int opt)
{
	mode_t		val;
	char		buf[1024];
	char		*curr_dir;

	curr_dir = RPW(grp, buf);
	val = (s_buf.st_mode & ~S_IFMT);
	if (!(*path) || access((*path), F_OK) != 0)
		error_cmd("unknown directory", (*path), 1);
	else if (!S_ISDIR(s_buf.st_mode) && !S_ISLNK(s_buf.st_mode))
		error_cmd("this is not a directory", (*path), 1);
	else if (!(val & S_IXUSR))
		error_cmd("Permission denied", (*path), 1);
	else if (chdir((*path)) == 0)
		update_pwd(grp, (*path), opt, curr_dir);
	ft_strdel(path);
}

char	*starting_replace(char *path, char *replace, char *by)
{
	char	buff[2048];
	char	tmp[2048];

	ft_bzero(buff, 2048);
	ft_bzero(tmp, 2048);
	ft_strcpy(buff, path);
	ft_strcpy(tmp, ft_strstr(buff, replace) + LEN(replace));
	ft_bzero(ft_strstr(buff, replace), LEN(path));
	ft_strcat(buff, by);
	ft_strcat(buff, tmp);
	return (ft_strdup(buff));
}

char	*replace_in_path(t_group *grp, t_parse *parse, int nb)
{
	char	*tmp;
	char	buf[1024 + 1];

	ft_bzero(buf, 1025);
	tmp = RPW(grp, buf);
	if (!ft_strstr(tmp, parse->cmdsplit[nb]))
	{
		error_cmd("Can't find in actual path", parse->cmdsplit[nb], 1);
		return (NULL);
	}
	tmp = starting_replace(tmp, parse->cmdsplit[nb], parse->cmdsplit[nb + 1]);
	return (tmp);
}
