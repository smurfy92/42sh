/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 20:23:03 by julio             #+#    #+#             */
/*   Updated: 2016/12/10 06:49:01 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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
		else if (parse->cmdsplit[3] == NULL)
			(*path) = SDUP(parse->cmdsplit[2]);
		else
			(*path) = replace_in_path(grp, parse, 2);
		ret = (parse->cmdsplit[1][1] == 'P') ? 1 : 0;
	}
	return (ret);
}

static void		cd_display_help(void)
{
	ft_putendl("usage: cd [ -L | -P | -h ] [ dirname ]");
	ft_putendl("cd is used to change the working directory.");
	ft_putendl("If 2 arguments are given to cd, the first ocurrence in PWD will be replaced by the second argument.");
	ft_putendl("-P : change directory using the physical path");
	ft_putendl("-L : change directory using the logical path");
	ft_putendl("-h : display help");
}

int		is_param(char c)
{
	if (c == 'P' || c == 'L' || c == 'h')
		return (1);
	return (0);
}

void	cd_helper(t_group *grp, t_parse *parse, char **path, int *opt)
{
	char	buf[1025];

	ft_bzero(buf, 1025);
	if (parse->cmdsplit[1][0] == '-' && is_param(parse->cmdsplit[1][1]))
		*opt = update_path_cd(path, parse, grp, 2);
	else if (parse->cmdsplit[1] && parse->cmdsplit[2])
		(*path) = replace_in_path(grp, parse, 1);
	else if (ft_strcmp(parse->cmdsplit[1], "..") != 0)
		(*path) = SDUP(parse->cmdsplit[1]);
	else
	{
		(*path) = SUB(RPW(grp, buf), 0,
			LEN(RPW(grp, buf)) - (LEN(ft_strrchr(RPW(grp, buf), '/')) - 1));
		if ((*path)[ft_strlen((*path)) - 1] == '/' && ft_strlen((*path)) > 1)
			(*path)[ft_strlen((*path)) - 1] = '\0';
	}
}

int		builtin_cd(t_group *grp, t_parse *parse)
{
	struct stat	s_buf;
	char		*path;
	int			opt;
	char		buf[1024 + 1];

	opt = 0;
	ft_bzero(buf, 1024);
	path = NULL;
	if (parse->cmdsplit[1] == NULL)
		path = return_home(grp, NULL);
	else if ((parse->cmdsplit[1][0] != '-' && parse->cmdsplit[2] &&
		parse->cmdsplit[3]) || (parse->cmdsplit[1][0] == '-' &&
		parse->cmdsplit[2] && parse->cmdsplit[3] && parse->cmdsplit[4]))
		error_cmd("Too many arguments", "cd", 1);
	else if ((parse->cmdsplit[1][0] == '-' && ft_strlen(parse->cmdsplit[1]) != 2))
		error_cmd("Too many options", "cd", 1);
	else if (parse->cmdsplit[1][0] == '-' && parse->cmdsplit[1][1] == false)
		update_path_cd(&path, parse, grp, 1);
	else if (parse->cmdsplit[1][0] == '-' && parse->cmdsplit[1][1] == 'h')// && ft_strlen(parse->cmdsplit[1]) == 2)
		cd_display_help();
	else
		cd_helper(grp, parse, &path, &opt);
	if (!path)
		return (1);
	lstat(path, &s_buf);
	cderr_pwd(grp, &path, s_buf, opt);
	return (1);
}
