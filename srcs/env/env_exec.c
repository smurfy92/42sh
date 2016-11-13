/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 22:59:42 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/13 01:54:58 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		create_exec_env(t_group *grp, char **cmd_split)
{
	int		fd;
	char	*path;
	char	**env;

	if (CMD(file) && (fd = open(CMD(file), O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	if (CMD(fd) > 0)
		dup2(CMD(fd), STDOUT_FILENO);
	ft_dup_redirection(grp->allcmd->andor->parselst);
	/*
	ret = is_builtins(cmd_split); 
	ici cest les binaire qui sont exec pas les builtins to check if we need to exec builtin
	*/
	printf("path_tmp %s\n", ENV(path_tmp));
	if (ENV(path_tmp) != NULL)
		hash_init(&grp->root, grp, ENV(path_tmp)); // leaks
	path = get_path(cmd_split[0], grp->root);
	printf("PATH: %s\n", path);
	if (check_cmd(&path, cmd_split[0]) == 0 && path)
	{
		env = ENV(lst_tmp) ? list_to_tab(ENV(lst_tmp)) : list_to_tab(ENV(lst));
		execve(path, cmd_split, env);
	}
	exit(EXIT_FAILURE);
}

void		init_exec_env(t_group *grp)
{
	char	**cmd_split;
	pid_t	pid;
	int		ret;

	cmd_split = ft_strsplit(ENV(cmd), ' ');
	pid = fork();
	pid == -1 ? exit(270) : 0;
	if (pid == 0)
		create_exec_env(grp, cmd_split);
	waitpid(pid, &ret, 0);
	if (ret > 0)
		grp->exit = 1;
	ft_freestrtab(&cmd_split);
}
