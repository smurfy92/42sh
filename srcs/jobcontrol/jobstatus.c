/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 23:09:06 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char	*update_status(int sig)
{
	char	*status;

	status = NULL;
	sig == SIGINT ? (status = SDUP("INTERRUPT")) : 0;
	status == NULL ? (status = SDUP("DONE")) : 0;
	return (status);
}

void	change_state(t_jobs *jobs, int code)
{
	REMOVE(&jobs->status);
	jobs->terminate = code;
	jobs->status = update_status(code);
	jobs->is_last = true;
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
			if (jobs->terminate > -1)
				remove_job(jobs);
		}
		jobs = jobs->next;
	}
	// update les + - nil
}