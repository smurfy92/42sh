/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:39:35 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/18 20:24:47 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		help_shlvl(t_group *grp)
{
	insert_env(grp, "SHLVL=1");
}

void		shlvl(t_group *grp)
{
	char	*shlvl;
	int		lvl;

	lvl = ft_atoi(ft_getenv(grp, "SHLVL"));
	lvl++;
	shlvl = ft_itoa(lvl);
	shlvl = JOINF("SHLVL=", shlvl, 2);
	insert_env(grp, shlvl);
	REMOVE(&shlvl);
}

void		help_pwd(t_group *grp)
{
	char	c_wd[4096 + 1];
	char	*pwd;

	ft_bzero(c_wd, 4096 + 1);
	getcwd(c_wd, 4096);
	pwd = ft_strjoin("PWD=", c_wd);
	insert_env(grp, pwd);
}

void		path_help(t_group *grp)
{
	char		line[4096 + 1];
	char		path[4096 + 1];
	int			ret;
	int			i;
	int			fd;

	if ((fd = open("/etc/paths", O_RDONLY)) < 0)
		return ;
	ft_bzero(line, 4096 + 1);
	ft_bzero(path, 4096 + 1);
	i = -1;
	while ((ret = read(fd, line, 4096)))
	{
		line[ret] = '\0';
		while (line[++i])
		{
			if (line[i] == '\n' && line[i + 1] == '\0')
				line[i] = '\0';
			if (line[i] == '\n')
				line[i] = ':';
		}
	}
	ft_strcat(path, "PATH=");
	ft_strcat(path, line);
	insert_env(grp, path);
}

void		home_helper(t_group *grp)
{
	char			log[4096];
	DIR				*dir_o;
	struct dirent	*cur_e;

	ft_bzero(log, 4096);
	if (ft_getenv(grp, "LOGNAME") == NULL)
	{
		ft_strcat(log, "LOGNAME=");
		ft_strcat(log, getlogin());
		insert_env(grp, log);
	}
	dir_o = opendir("/Users");
	while ((cur_e = readdir(dir_o)))
	{
		if (ft_strcmp(cur_e->d_name, ft_getenv(grp, "LOGNAME")) == 0 &&
			(cur_e->d_type & DT_DIR))
		{
			ft_bzero(log, 4096);
			ft_strcat(log, "HOME=");
			ft_strcat(log, "/Users/");
			ft_strcat(log, cur_e->d_name);
			insert_env(grp, log);
		}
	}
}
