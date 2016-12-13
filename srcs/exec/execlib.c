/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 22:45:03 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 13:55:57 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			check_cmd(char **path, char *cmd)
{
	struct stat	s_buf;
	mode_t		val;
	int			ret;

	if (*path == NULL)
		*path = SDUP(cmd);
	ret = lstat(*path, &s_buf);
	val = (s_buf.st_mode & ~S_IFMT);
	if (ret != 0)
		error_cmd("command not found", cmd, 1);
	else if (s_buf.st_size <= 0)
		error_cmd("executable format error", cmd, 1);
	else if (!(val & S_IXUSR) || S_ISDIR(s_buf.st_mode))
		error_cmd("Permission denied", cmd, 1);
	else
		return (0);
	return (-1);
}

void		ft_dup_redirection(t_parse *parse)
{
	char	**tmp;
	int		i;

	if (parse->redfd)
	{
		tmp = ft_strsplit(parse->redfd, '>');
		parse->fd = dup2(ft_atoi(tmp[1]), ft_atoi(tmp[0]));
		REMOVE(&tmp[0]);
		REMOVE(&tmp[1]);
		free(tmp);
	}
	if (parse->closefd)
	{
		tmp = ft_strsplit(parse->closefd, ';');
		i = -1;
		while (tmp[++i])
		{
			close(ft_atoi(tmp[i]));
			REMOVE(&tmp[i]);
		}
		free(tmp);
	}
}

void		control_process(t_jobs **parent, t_parse *tmp,
								int *tabl, char *andorcmd)
{
	t_jobs	*jobs;
	t_group	*grp;

	grp = get_grp();
	jobs = control_jobs(parent, grp, tmp->cmd, andorcmd);
	jobs->fdin = grp->pipefd_in;
	if (grp->is_interact == true)
		setpgid(jobs->pid, (*parent)->pid);
	if (tmp->next)
		grp->pipefd_in = tabl[0];
	else
	{
		close(tabl[0]);
		grp->pipefd_in = STDIN_FILENO;
	}
	close(tabl[1]);
}

void		generate_process(t_jobs **parent, t_parse *tmp,
									char *andorcmd, int fg)
{
	int		tabl[2];
	t_group	*grp;

	pipe(tabl);
	grp = get_grp();
	grp->father = fork();
	grp->father < 0 ? ft_exit(grp, 999) : 0;
	if (grp->father == 0)
	{
		close(tabl[0]);
		init_shell_job(*parent ? (*parent)->pid : 0, fg);
		if (tmp->next && tmp->fd == -1)
			ft_fork_pipe(grp, tmp, tabl[1]);
		else
		{
			close(tabl[1]);
			exec_child(grp, tmp);
		}
	}
	else
		control_process(parent, tmp, tabl, andorcmd);
}

void		generate_builtin(t_jobs **parent, t_parse *tmp,
									char *andorcmd, int fg)
{
	t_group	*grp;
	t_jobs	*jobs;

	grp = get_grp();
	grp->father = 42;
	ENV(fg) = fg;
	ENV(pgid) = *parent;
	builtins(grp, tmp);
	jobs = control_jobs(parent, grp, tmp->cmd, andorcmd);
	jobs->fdin = grp->pipefd_in;
	if (grp->father != 42 && grp->is_interact == true)
		setpgid(jobs->pid, (*parent)->pid);
	else if (grp->father == 42)
		change_state(jobs, 1);
}
