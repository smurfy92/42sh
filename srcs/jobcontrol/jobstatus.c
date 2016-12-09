/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 06:36:33 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char	*update_status(int sig)
{
	char	*status;

	status = NULL;
	sig == CLD_CONTINUED ? (status = SDUP("CONTINUED")) : 0;
	sig == CLD_STOPPED ? (status = SDUP("SUSPENDED")) : 0;
	sig == CLD_TRAPPED ? (status = SDUP("TRAPPED")) : 0;
	sig == CLD_DUMPED ? (status = SDUP("DUMPED")) : 0;
	sig == CLD_KILLED ? (status = SDUP("INTERRUPT")) : 0;
	sig == CLD_EXITED ? (status = SDUP("EXITED")) : 0;
	status == NULL ? (status = SDUP("UNKNOWN STATUS: TERMINATED")) : 0;
	return (status);
}

void	change_state(t_jobs *jobs, int code)
{
	if (jobs == NULL)
		return ;
	REMOVE(&jobs->status);
	jobs->terminate = code;
	jobs->status = update_status(code);
	jobs->enabled = (code == 1 || code == 2) ? false : true;
	if (jobs->enabled == false)
		if (jobs->fdin > 2)
			close(jobs->fdin);
	if (code > 1 && jobs->parent_cmd != NULL)
		display_jobs(jobs, 1, 1);
}

void	analyse_ret(t_jobs *jobs, int ret, int code)
{
	jobs->code = code;
	if (jobs->enabled == true || jobs->terminate == CLD_STOPPED)
	{	
		if (ret == jobs->pid && WIFCONTINUED(code))
			change_state(jobs, CLD_CONTINUED);
		else if (ret == jobs->pid && WIFSTOPPED(code))
			change_state(jobs, CLD_STOPPED);
		else if (ret == jobs->pid && WIFEXITED(code))
			change_state(jobs, CLD_EXITED);
		else if (ret == jobs->pid)
			change_state(jobs, CLD_KILLED);
		else if (ret == -1 && jobs->terminate == -1)
			change_state(jobs, 0);
	}
}

void	check_jobs_status(t_jobs *jobs)
{
	t_jobs		*pipe;
	int			ret;
	int			code;

	if (jobs)
	{
		ret = waitpid(jobs->pid, &code, WNOHANG | WUNTRACED | WCONTINUED);
		analyse_ret(jobs, ret, code);
		pipe = jobs->next_pipe;
		while (pipe)
		{
			ret = waitpid(pipe->pid, &code, WNOHANG | WUNTRACED | WCONTINUED);
			analyse_ret(pipe, ret, code);
			pipe = pipe->next_pipe;
		}
	}
}

void	jobs_status(t_group *grp)
{
	t_jobs		*jobs;

	jobs = grp->jobs;
	while (jobs)
	{
		check_jobs_status(jobs);
		jobs = jobs->next;
	}
}