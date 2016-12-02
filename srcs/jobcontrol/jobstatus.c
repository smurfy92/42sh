/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/02 05:08:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char	*update_status(int sig)
{
	char	*status;

	status = NULL;
	sig == SIGINT ? (status = SDUP("INTERRUPT")) : 0;
	sig == SIGTSTP ? (status = SDUP("SUSPENDED")) : 0;
	sig == SIGSEGV ? (status = SDUP("SEGFAULT")) : 0;
	status == NULL ? (status = SDUP("DONE")) : ft_putchar_fd('\n', 2);
	return (status);
}

void	change_state(t_jobs *jobs, int code)
{
	REMOVE(&jobs->status);
	jobs->terminate = code;
	jobs->status = update_status(code);
	jobs->is_last = true;
	if (code > 0)
	{
		display_jobs(jobs->idx, jobs->pid, 0);
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(jobs->status, 2);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(jobs->cmd, 2);
	}
}

void	jobs_states(t_group *grp)
{
	t_jobs		*jobs;
	int			ret;
	int			code;

	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs->pid > 0)
		{	
			ret = waitpid(jobs->pid, &code, WNOHANG);
			if (ret == jobs->pid)
				change_state(jobs, code);
		}
		jobs = jobs->next;
	}
}

void	remove_job(t_jobs *jobs)
{
	REMOVE(&jobs->cmd);
	REMOVE(&jobs->status);
	jobs->pid = -1;
	jobs->terminate = -1;
	jobs->is_last = false;
	jobs->is_prelast = false;
}

void	jobs_update(t_group *grp)
{
	t_jobs		*jobs;
	int			ret;
	int			code;

	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs->pid > 0)
		{
			ret = waitpid(jobs->pid, &code, WNOHANG);
			if (jobs->terminate > -1 && jobs->terminate != 18)
				remove_job(jobs);
		}
		jobs = jobs->next;
	}
	// update les + - nil
}