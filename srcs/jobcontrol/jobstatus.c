/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/27 22:25:56 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

// void	jobs_status(t_group *grp)
// {
// 	t_jobs		*jobs;
// 	t_jobs		*next;
// 	t_jobs		*prev;
// 	int			ret;
// 	int			code;

// 	jobs = grp->jobs;
// 	prev = NULL;
// 	while (jobs)
// 	{
// 		next = jobs->next;
// 		ret = waitpid(jobs->pid, &code, WNOHANG);
// 		if (ret == jobs->pid)
// 		{	
// 			REMOVE(&jobs->cmd);
// 			free(jobs);
// 			jobs = NULL;
// 			if (prev)
// 				prev->next = next;
// 			else if (prev == NULL && next != NULL)
// 				grp->jobs = next;
// 			else if (prev == NULL && next == NULL)
// 				grp->jobs = NULL;
// 		}
// 		else
// 			prev = jobs;
// 		jobs = next;
// 	}
// }

// typedef struct s_jobs
// {
// 	int				idx;
// 	pid_t			pid;
// 	int				status;
// 	int				is_last;
// 	int				is_prelast;
// 	char			*cmd;
// 	int				terminate;
// 	struct s_jobs	*next;
// }				t_jobs;

// void	jobs_states(t_group *grp)
// {
// 	t_jobs		*jobs;
// 	int			ret;
// 	int			code;

// 	jobs = grp->jobs;
// 	while (jobs)
// 	{
// 		if (jobs->pid > 0)
// 		{	
// 			ret = waitpid(jobs->pid, &code, WNOHANG);
// 			if (ret == jobs->pid)
// 			{	
// 				jobs->terminate = code;
// 				jobs->status = 
// 			}
// 		}
// 		jobs = jobs->next;
// 	}
// }

void	jobs_status(t_group *grp) //jobs_update
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
			{	
				REMOVE(&jobs->cmd);
				jobs->pid = -1;
				// jobs->status = analyse_retcode(code);
				jobs->terminate = code;
				jobs->is_last = true;
				jobs->is_prelast = false;
			}
		}
		jobs = jobs->next;
	}
}