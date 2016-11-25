/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:18:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/25 23:38:10 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	REMOVE(&jobs->cmd);
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = 0;
	jobs->cmd = SDUP(cmd);
	jobs->is_last = true;
	jobs->is_prelast = false;
	jobs->terminate = 0;
}

void		create_jobs(t_group *grp, char *cmd, int pid, int ret)
{
	t_jobs	*tmp;
	int		count;

	if (ret)
		;
	count = 0;
	if (grp->jobs == NULL)
	{
		grp->jobs = (t_jobs *)malloc(sizeof(t_jobs));
		fill_jobs(grp->jobs, 1, pid, cmd);
		return ;
	}
	tmp = grp->jobs;
	while (tmp->next)
	{
		count++;
		if (tmp->terminate)
			fill_jobs(tmp, tmp->idx, pid, cmd);
		tmp = tmp->next;
	}
	tmp = (t_jobs *)malloc(sizeof(t_jobs));
	fill_jobs(tmp, count, pid, cmd);
}

void		init_shell_job(int pgid)
{
	int	pid;
	int	is_interact;

	is_interact = isatty (STDIN_FILENO);
	if (is_interact)
	{
		pid = getpid ();
		if (pgid == 0) 
			pgid = pid;
		setpgid (pid, pgid);

		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
}

void		jobs_exec(t_group *grp, t_andor *andor)
{
	t_parse		*tmp;
	pid_t		pid;

	tmp = andor->parselst;
	pid = fork();
	pid < 0 ? ft_exit(grp, 999) : 0;
	init_shell_job(pid);
	if (pid == 0)
	{
		init_shell_job(pid);
		while (tmp)
		{
			if (!tmp->fail)
			{
				if (tmp->next && tmp->fd == -1)
				{
					ft_fork_pipe(grp, tmp);
				}
				else
				{
					exec_child(1, grp, tmp);
				}
			}
			tmp = tmp->next;
		}
		ft_exit(grp, EXIT_FAILURE);
	}
	// waitpid(pid, &ret, WNOHANG);
	// printf("ret : %d\n", ret);
	//create_jobs(grp, andor->cmd, pid, 0);
}

void	init_job_control(t_group *grp, t_andor *andor)
{
    jobs_exec(grp, andor);
}