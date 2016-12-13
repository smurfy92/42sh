/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobstatus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 00:13:31 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 10:14:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char	*update_status(int sig, int code)
{
	char	*status;

	status = NULL;
	sig == SIGPIPE ? (status = SDUP("broken pipe")) : 0;
	sig == SIGINT ? (status = SDUP("interrupt")) : 0;
	sig == SIGKILL ? (status = SDUP("killed")) : 0;
	sig == SIGTERM ? (status = SDUP("terminated")) : 0;
	sig == SIGBUS ? (status = SDUP("bus error")) : 0;
	sig == SIGABRT ? (status = SDUP("abort")) : 0;
	sig == SIGSEGV ? (status = SDUP("segmentation fault")) : 0;
	sig == SIGNCONT ? (status = SDUP("continued")) : 0;
	if (sig == SIGNSTOP)
		status = SDUP(JOINF("suspended: ", ft_itoa(WSTOPSIG(code)), 2));
	if (sig == CLD_EXITED)
		status = SDUP(JOINF("exited: ", ft_itoa(WEXITSTATUS(code)), 2));
	sig == 0 ? (status = SDUP(JOINF("done: ", ft_itoa(code), 2))) : 0;
	status == NULL ? (status = SDUP("UNKNOWN STATUS: terminated")) : 0;
	return (status);
}

void	change_state(t_jobs *jobs, int code)
{
	t_group *grp;

	grp = get_grp();
	if (jobs == NULL)
		return ;
	REMOVE(&jobs->status);
	jobs->terminate = code;
	jobs->status = update_status(code, jobs->code);
	jobs->enabled = (code != SIGNCONT) ? false : true;
	if (jobs->enabled == false && code != SIGNSTOP && jobs->fdin > 2)
		if (close(jobs->fdin) < 0)
			perror("closed");
	if (code > 1 && jobs->parent_cmd != NULL)
		display_jobs(jobs, 1, 1);
	else if (code > 1 && tcgetpgrp(STDIN_FILENO) == grp->program_pid)
		display_jobs(jobs, 1, 0);
}

void	analyse_ret(t_jobs *jobs, int ret, int code)
{
	if (jobs->enabled == true || jobs->terminate == SIGNSTOP)
		jobs->code = code;
	if (ret == jobs->pid && WIFCONTINUED(code))
		change_state(jobs, SIGNCONT);
	else if (ret == jobs->pid && WIFSTOPPED(code))
		change_state(jobs, SIGNSTOP);
	else if (ret == jobs->pid && WIFEXITED(code))
		change_state(jobs, CLD_EXITED);
	else if (ret == jobs->pid && code < 35)
		change_state(jobs, code);
	else if (ret == jobs->pid)
		change_state(jobs, 0);
}

int		check_group_status(t_jobs *pgid, int free)
{
	int		ret;
	int		code;
	t_jobs	*jobs;

	ret = waitpid(-pgid->pid, &code, WNOHANG | WUNTRACED | WCONTINUED);
	if (ret > 0 && (jobs = get_jobs_pid(ret)))
		analyse_ret(jobs, ret, code);
	else if (ret == -1)
	{
		if (free)
			remove_jobs(pgid->pid);
		return (-1);
	}
	return (0);
}

void	jobs_status(t_group *grp)
{
	t_jobs		*jobs;
	t_jobs		*pipe;
	int			ret;
	int			code;

	jobs = grp->jobs;
	while (jobs)
	{
		pipe = jobs;
		while (pipe)
		{
			ret = waitpid(pipe->pid, &code, WNOHANG | WUNTRACED | WCONTINUED);
			if (ret > 0)
				analyse_ret(pipe, ret, code);
			pipe = pipe->next_pipe;
		}
		jobs = jobs->next;
	}
}
