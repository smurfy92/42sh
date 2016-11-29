/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 05:20:15 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	change_state(t_jobs *jobs, int code)
{
	jobs->terminate = code;
	jobs->status = SDUP("DONE");
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
				change_state(code);
		}
		jobs = jobs->next;
	}
}

void	update_job(t_jobs *jobs, int sig)
{
	REMOVE(&jobs->cmd);
	jobs->pid = -1;
	jobs->is_last = true;
	jobs->is_prelast = false;
}

void	jobs_update(t_group *grp) //jobs_update
{
	t_jobs		*jobs;
	int			ret;
	int			code;
	//siginfo_t	info;

	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs->pid > 0)
		{
			ret = waitpid(jobs->pid, &code, WNOHANG);
			if (jobs->terminate > -1)
				update_job(jobs, code);
		}
		jobs = jobs->next;
	}
}