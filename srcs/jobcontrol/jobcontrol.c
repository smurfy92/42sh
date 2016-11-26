/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:18:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/26 01:20:59 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	//REMOVE(&jobs->cmd);
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = 0;
	jobs->cmd = SDUP(cmd);
	jobs->is_last = true;
	jobs->is_prelast = false;
	jobs->terminate = 0;
	jobs->next = NULL;
}

void		create_jobs(t_group *grp, char *cmd, int pid)
{
	t_jobs		*tmp;
	t_jobs		*tmp2;
	int			count;

	count = 2;
	tmp = (t_jobs *)malloc(sizeof(t_jobs));
	fill_jobs(tmp, 1, pid, cmd);
	if (!grp->jobs)
		grp->jobs = tmp;
	else
	{
		tmp2 = grp->jobs;
		while (tmp2 && tmp2->next)
		{
			count++;
			tmp2 = tmp2->next;
		}
		tmp2->next = tmp;
		tmp2->next->idx = count;
	}
}

void		init_shell_job(int pgid)
{
	int	pid;
	int	is_interact;

	is_interact = isatty (STDIN_FILENO);
	if (is_interact)
	{
		pid = getpid ();
		pgid == 0 ? (pgid = pid) : 0;
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
	int			ret;

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
					ft_fork_pipe(grp, tmp); // <-- stocker la commande dans jobs how ? fd ?
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
	create_jobs(grp, andor->cmd, pid);
	waitpid(pid, &ret, WNOHANG);
}

void	init_job_control(t_group *grp, t_andor *andor)
{
    jobs_exec(grp, andor);
}