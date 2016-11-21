/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 20:23:03 by julio             #+#    #+#             */
/*   Updated: 2016/11/21 23:27:40 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

#define RPW(x, y) (ft_getenv(x, "PWD")) ? ft_getenv(x, "PWD") : getcwd(y, 1024)

void	cderr_pwd(t_group *grp, char **path, struct stat s_buf, int opt)
{
	mode_t		val;
	char		buf[1024];
	char		*curr_dir;

	curr_dir = RPW(grp, buf);
	val = (s_buf.st_mode & ~S_IFMT);
	if (access((*path), F_OK) != 0)
		error_cmd("unknown directory", (*path), 1);
	else if (!S_ISDIR(s_buf.st_mode) && !S_ISLNK(s_buf.st_mode))
		error_cmd("this is not a directory", (*path), 1);
	else if (!(val & S_IXUSR))
		error_cmd("Permission denied", (*path), 1);
	else if (chdir((*path)) == 0)
		update_pwd(grp, (*path), opt, curr_dir);
	ft_strdel(path);
}

char	*return_home(t_group *grp, char **path)
{
	char	*ret;

	if (path)
	{
		(*path) = SDUP(ft_getenv(grp, "OLDPWD"));
		ft_putstr("> ");
		ft_putendl((*path));
		return (NULL);
	}
	if (ft_getenv(grp, "HOME") != NULL)
	{
		ret = SDUP(ft_getenv(grp, "HOME"));
		return (ret);
	}
	else
		return (SDUP("HOME has been unset from environnement !"));
}

int		update_path_cd(char **path, t_parse *parse, t_group *grp, int mode)
{
	int		ret;

	ret = 0;
	if (mode == 1)
	{
		if (ft_getenv(grp, "OLDPWD") != NULL)
			return_home(grp, path);
		else
			(*path) = SDUP("OLDPWD has been unset from environnement !");
	}
	else if (mode == 2)
	{
		if (parse->cmdsplit[2] == NULL)
			(*path) = return_home(grp, NULL);
		else
			(*path) = SDUP(parse->cmdsplit[2]);
		ret = (parse->cmdsplit[1][1] == 'P') ? 1 : 0;
	}
	return (ret);
}

int		is_param(char c)
{
	if (c == 'P' || c == 'L')
		return (1);
	return (0);
}

int		builtin_cd(t_group *grp, t_parse *parse)
{
	struct stat	s_buf;
	char		*path;
	int			opt;
	char		buf[1024 + 1];

	opt = 0;
	ft_bzero(buf, 1024);
	if (parse->cmdsplit[1] == NULL)
		path = return_home(grp, NULL);
	else if (parse->cmdsplit[1][0] == '-' && parse->cmdsplit[1][1] == false)
		update_path_cd(&path, parse, grp, 1);
	else if (parse->cmdsplit[1][0] == '-' && is_param(parse->cmdsplit[1][1]))
		opt = update_path_cd(&path, parse, grp, 2);
	else if (ft_strcmp(parse->cmdsplit[1], "..") != 0)
		path = SDUP(parse->cmdsplit[1]);
	else
	{
		path = SUB(RPW(grp, buf), 0,
			LEN(RPW(grp, buf)) - (LEN(ft_strrchr(RPW(grp, buf), '/')) - 1));
		if (path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1)
			path[ft_strlen(path) - 1] = '\0';
	}
	lstat(path, &s_buf);
	cderr_pwd(grp, &path, s_buf, opt);
	return (1);
}
