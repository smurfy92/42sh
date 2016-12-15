/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:48:45 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 16:07:16 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		cderr_pwd(t_group *grp, char **path, struct stat s_buf, int opt)
{
	mode_t		val;
	char		buf[1024];
	char		*curr_dir;
	char		bf[1024];

	curr_dir = RPW(grp, buf);
	ft_bzero(bf, 1024);
	val = (s_buf.st_mode & ~S_IFMT);
	ft_strcpy(bf, *path);
	ft_strdel(path);
	if (!ft_strlen(bf) || access(bf, F_OK) != 0)
		error_cmd("unknown directory", bf, 1);
	else if (!S_ISDIR(s_buf.st_mode) && !S_ISLNK(s_buf.st_mode))
		error_cmd("this is not a directory", bf, 1);
	else if (!(val & S_IXUSR))
		error_cmd("Permission denied", bf, 1);
	else if (chdir(bf) == 0)
		update_pwd(grp, bf, opt, curr_dir);
}

char		*starting_replace(char *path, char *replace, char *by)
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

char		*replace_in_path(t_group *grp, t_parse *parse, int nb)
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

void		cd_display_help(void)
{
	ft_putendl("usage: cd [ -L | -P | -h ] [ dirname ]");
	ft_putendl("cd is used to change the working directory.");
	ft_putstr("If 2 arguments are given to cd, the first ocurrence i");
	ft_putendl("PWD will be replaced by the second argument.");
	ft_putendl("-P : change directory using the physical path");
	ft_putendl("-L : change directory using the logical path");
	ft_putendl("-h : display help");
}
