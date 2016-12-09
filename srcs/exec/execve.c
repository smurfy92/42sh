/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 23:37:23 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 02:34:19 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		prepare_bquotes(t_group*grp, t_parse *parse, int *fd, char **cmdsplit)
{
	cmdsplit[0] = ft_getenv(grp, "_"); // rajouter a l'env -i "_" !
	cmdsplit[1] = NULL;
	fd[0] = open("/tmp/.to_shell", O_WRONLY | O_CREAT | O_TRUNC,
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	ft_putstr_fd(parse->bquotes, fd[0]);
	close(fd[0]);
	fd[0] = open("/tmp/.to_shell", O_RDONLY);
	fd[1] = open("/tmp/.fromshell", O_WRONLY | O_CREAT | O_TRUNC,
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
}

void		exec_bquotes(t_group *grp, t_parse *parse)
{
	pid_t	pid;
	int		fd[2];
	int		ret;
	char	**env;
	char	*cmdsplit[2];

	prepare_bquotes(grp, parse, fd, cmdsplit);
	pid = fork();
	grp->program_pid = pid;
	pid < 0 ? ft_exit(grp, 999) : 0;
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		env = list_to_tab(ENV(lst));
		execve(cmdsplit[0], cmdsplit, env);
		ft_freestrtab(&env);
		ft_exit(grp, 0);
	}
	waitpid(pid, &ret, 0);
	close(fd[0]);
	close(fd[1]);
	grp->program_pid = getpid();
}

void		exec_child(t_group *grp, t_parse *parse)
{
	int		fd;
	int		ret;
	char	*path;
	char	**env;

	dup2(grp->pipefd_in, STDIN_FILENO);
	if (parse->file && (fd = open(parse->file, O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	if (parse->fd > 0)
		dup2(parse->fd, STDOUT_FILENO);
	ft_dup_redirection(parse);
	ret = is_builtins(parse->cmdsplit);
	path = get_path(parse->cmdsplit[0], grp->root);
	if (ret == 0 && check_cmd(&path, parse->cmdsplit[0]) == 0 && path)
	{
		env = list_to_tab(ENV(lst));
		execve(path, parse->cmdsplit, env);
		ft_freestrtab(&env);
	}
	else if (ret == 0)
		ft_exit(grp, EXIT_FAILURE);
	else if (ret == 1)
		builtins(grp, parse);
	ft_exit(grp, grp->exit);
}

void		ft_fork_exec(t_group *grp, t_parse *parse, int pipefd_out)
{
	char	*path;
	char	**env;
	int		ret;

	ret = is_builtins(parse->cmdsplit);
	path = get_path(parse->cmdsplit[0], grp->root);
	if (ret == 0 && check_cmd(&path, parse->cmdsplit[0]) == 0 && path)
	{
		env = list_to_tab(ENV(lst));
		execve(path, parse->cmdsplit, env);
	}
	close(pipefd_out);
	if (ret == 1)
		builtins(grp, parse);
	else
		ft_exit(grp, EXIT_FAILURE);
	ft_exit(grp, grp->exit);
}

void		ft_fork_pipe(t_group *grp, t_parse *parse, int pipefd_out)
{
	int		fd;

	dup2(grp->pipefd_in, STDIN_FILENO);
	if (parse->file && (fd = open(parse->file, O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	dup2(pipefd_out, STDOUT_FILENO);
	ft_dup_redirection(parse);
	ft_fork_exec(grp, parse, pipefd_out);
}
