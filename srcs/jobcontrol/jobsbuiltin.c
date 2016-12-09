/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 00:53:40 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 02:34:13 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

// void	remove_job(t_jobs *jobs)
// {
// 	if (jobs->pid > 0 && jobs->terminate > -1 &&
// 		jobs->terminate != CLD_STOPPED && jobs->terminate != CLD_CONTINUED)
// 	{
// 		REMOVE(&jobs->cmd);
// 		REMOVE(&jobs->status);
// 		jobs->pid = -1;
// 		jobs->terminate = -1;
// 		jobs->is_last = false;
// 		jobs->is_prelast = false;
// 	}
// }

// void	remove_jobs_pipe(t_jobs *parent)
// {
// 	t_jobs	*tmp;
// 	t_jobs	*pipe;
	
// 	pipe = parent->next_pipe;
// 	while (pipe)
// 	{
// 		tmp = pipe->next_pipe;
// 		remove_job(pipe);
// 		free(pipe);
// 		pipe = tmp;
// 	}
// 	parent->next_pipe = NULL;
// }

// void	jobs_update(t_group *grp)
// {
// 	t_jobs		*jobs;

// 	jobs = grp->jobs;
// 	while (jobs)
// 	{
// 		remove_job(jobs);
// 		remove_jobs_pipe(jobs);
// 		jobs = jobs->next;
// 	}
// 	// update les + - nil
// }

int	builtin_jobs(t_group *grp)
{
	t_jobs	*tmp;
	t_jobs	*pipe;

	tmp = grp->jobs;
	while (tmp)
	{
		if (tmp->pid > 0 || tmp->next_pipe)
		{
			display_jobs(tmp, 1);
			pipe = tmp->next_pipe;
			while(pipe)
			{
				display_jobs(pipe, 1);
				pipe = pipe->next_pipe;
			}
		}
		tmp = tmp->next;
	}
	//jobs_update(grp);
	return (1);
}
