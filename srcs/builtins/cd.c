/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/02 14:30:40 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	cderr_pwd(t_group *grp, char *path, struct stat s_buf)
{
	mode_t		val;
	char		buf[1024];
	char		*old_pwd;
	char		*pwd;
	char		*curr_dir;

	curr_dir = getcwd(buf, 1024);
	val = (s_buf.st_mode & ~S_IFMT);
	if (access(path, F_OK) != 0)
		error_cmd("unknown directory", path, 1);
	else if (!S_ISDIR(s_buf.st_mode) && !S_ISLNK(s_buf.st_mode))
		error_cmd("this is not a directory", path, 1);
	else if (!(val & S_IXUSR))
		error_cmd("Permission denied", path, 1);
	else if (chdir(path) == 0)
	{
		old_pwd = JOIN("OLDPWD=", curr_dir);
		pwd = JOIN("PWD=", getcwd(buf, 1024));
		insert_env(grp, pwd);
		insert_env(grp, old_pwd);
		REMOVE(&old_pwd);
		REMOVE(&pwd);
		grp->exit = 0;
	}
}

int		builtin_cd(t_group *grp)
{
	struct stat	s_buf;
	char		*path;

	if (CMD(cmdsplit)[1] == NULL)
	{
		path = ft_getenv(grp, "HOME") ? SDUP(ft_getenv(grp, "HOME")) :
		SDUP("HOME has been unset from environnement !");
	}
	else if (CMD(cmdsplit)[1][0] == '-' && CMD(cmdsplit)[1][1] == false)
	{
		if (ft_getenv(grp, "OLDPWD") != NULL)
		{
			path = SDUP(ft_getenv(grp, "OLDPWD"));
			ft_putstr("> ");
			ft_putendl(path);
		}
		else
			path = SDUP("OLDPWD has been unset from environnement !");
	}
	else
		path = SDUP(CMD(cmdsplit)[1]);
	lstat(path, &s_buf);
	cderr_pwd(grp, path, s_buf);
	REMOVE(&path);
	return (1);
}
