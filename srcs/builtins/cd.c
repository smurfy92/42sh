/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 19:26:28 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static char		*join_path(t_group *grp, char *path)
{
	char	*tmp;
	char	*result;
	char	buff[1024 + 1];

	ft_bzero(buff, 1025);
	tmp = ft_strjoin("PWD=", (ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buff, 1024));
	if (tmp[ft_strlen(tmp) - 1] != '/')
		tmp = JOINF(tmp, "/", 1);
	result = JOIN(tmp, path);
	return (result);
}

void			cderr_pwd(t_group *grp, char *path, struct stat s_buf, int opt)
{
	mode_t		val;
	char		buf[1024];
	char		*old_pwd;
	char		*pwd;
	char		*curr_dir;

	curr_dir = (ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024);
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
		if (opt)
			pwd = JOIN("PWD=", getcwd(buf, 1024));
		else if (ft_strcmp(path, "..") != 0 && ft_strcmp(path, ".") != 0)
			pwd = (path[0] == '/') ? JOIN("PWD=", path) : join_path(grp, path);
		else if (ft_strcmp(path, "..") == 0)
		{
			ft_putendl("ICI--->");
			ft_putnbr(ft_strlen((ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024)) - (ft_strlen(ft_strrchr((ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024), '/')) - 1));
			ft_putendl("");
			curr_dir = ft_strsub((ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024), 0, ft_strlen((ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024)) - (ft_strlen(ft_strrchr((ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024), '/')) - 1));
			if (curr_dir[ft_strlen(curr_dir) - 1] == '/' && ft_strlen(curr_dir) > 1)
				curr_dir[ft_strlen(curr_dir) - 1] = '\0';
			pwd = JOIN("PWD=", curr_dir);
			ft_strdel(&curr_dir);
		}
		insert_env(grp, pwd);
		insert_env(grp, old_pwd);
		REMOVE(&old_pwd);
		REMOVE(&pwd);
		grp->exit = 0;
	}
}

int		builtin_cd(t_group *grp, t_parse *parse)
{
	struct stat	s_buf;
	char		*path;
	int			opt;

	opt = 0;
	if (parse->cmdsplit[1] == NULL)
	{
		path = ft_getenv(grp, "HOME") ? SDUP(ft_getenv(grp, "HOME")) :
		SDUP("HOME has been unset from environnement !");
	}
	else if (parse->cmdsplit[1][0] == '-' && parse->cmdsplit[1][1] == false)
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
	else if (parse->cmdsplit[1][0] == '-' && (parse->cmdsplit[1][1] == 'P' || parse->cmdsplit[1][1] == 'L'))
	{
		if (parse->cmdsplit[2] == NULL)
		{
			path = ft_getenv(grp, "HOME") ? SDUP(ft_getenv(grp, "HOME")) :
				SDUP("HOME has been unset from environnement !");
		}
		else
			path = SDUP(parse->cmdsplit[2]);
		opt = (parse->cmdsplit[1][1] == 'P') ? 1 : 0;
	}
	else
		path = SDUP(parse->cmdsplit[1]);
	lstat(path, &s_buf);
	cderr_pwd(grp, path, s_buf, opt);
	REMOVE(&path);
	return (1);
}
