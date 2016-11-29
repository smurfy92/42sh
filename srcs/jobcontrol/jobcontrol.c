/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:18:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 05:19:41 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = 0;
	jobs->cmd = SDUP(cmd);
	jobs->is_last = true;
	jobs->is_prelast = false;
	jobs->terminate = -1;
}

void		display_jobs(int idx, int pid)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(idx, 2);
	ft_putstr_fd("] ", 2);
	ft_putnbr_fd(pid, 2);
	ft_putchar('\n');
}

void		create_jobs(t_group *grp, char *cmd, int pid)
{
	t_jobs		*tmp;
	t_jobs		*tmp2;
	int			count;

	count = 2;
	tmp = (t_jobs *)malloc(sizeof(t_jobs));
	tmp->next = NULL;
	fill_jobs(tmp, 1, pid, cmd);
	if (!grp->jobs)
		grp->jobs = tmp;
	else
	{
		tmp2 = grp->jobs;
		while (tmp2 && (tmp2->next || tmp2->pid == -1))
		{
			count++;
			if (tmp2->pid == -1)
			{
				REMOVE(&tmp->cmd); free(tmp);
				fill_jobs(tmp2, tmp2->idx, pid, cmd);
				return (display_jobs(tmp2->idx, pid));
			}
			tmp2 = tmp2->next;
		}
		tmp2->next = tmp;
		tmp2->next->idx = count;
	}
	display_jobs(tmp->idx, pid);
}

void		init_shell_job(int pgid)
{
	int	pid;
	int	is_interact;

	printf("JOBS_manage_shell \n");
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
	if (pid == 0)
	{
		while (tmp)
		{
			if (!tmp->fail)
			{
				if (tmp->next && tmp->fd == -1)
					ft_fork_pipe(grp, tmp); // <-- stocker la commande dans jobs how ? fd ?
				else
				{
					init_shell_job(pid);
					exec_child(1, grp, tmp);
				}
			}
			tmp = tmp->next;
		}
		ft_exit(grp, EXIT_FAILURE);
	}
	create_jobs(grp, andor->cmd, pid);
	if (grp->is_interact)
		setpgid (pid, pid);
	waitpid(pid, &ret, WNOHANG);
}

void	init_job_control(t_group *grp, t_andor *andor)
{
    jobs_exec(grp, andor);
}