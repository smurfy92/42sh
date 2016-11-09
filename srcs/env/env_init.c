/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:39:35 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/09 16:04:30 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		init_env(t_group *grp, char **env)
{
	int		i;

	i = -1;
	while (env && env[++i])
		insert_env(grp, env[i]);
	if (ft_getenv(grp, "HOME") == NULL)
		;
	if (ft_getenv(grp, "PATH") == NULL)
		HELP_PATH(grp);
	if (ft_getenv(grp, "TERM") == NULL)
		;
	if (ft_getenv(grp, "SHLVL") == NULL)
		help_shlvl(grp);
}


void		help_shlvl(t_group *grp)
{
	insert_env(grp, "SHLVL=1");
}


/*
** recupere le path avec env-i
*/

void		mac_pathhelp(t_group *grp)
{
	pid_t		father;
	int			fd;
	char		line[4096];
	int			ret;
	char		**result;

	father = fork();
	ft_bzero(line, 4096);
	if (father == 0)
	{
		fd = open(".pathhelp", O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd, 1);
		execve("/usr/libexec/path_helper", NULL, NULL);
		close (fd);
		exit(0);
	}
	else
	{
		wait(0);
		fd = open(".pathhelp", O_RDONLY);
		if ((ret = read(fd, line, 4096)))
		{
			line[ret] = '\0';
			close(fd);
			result = ft_strsplit(line, ';');
			insert_env(grp, result[0]);
			ft_freestrtab(&result);
		}
	}
}
