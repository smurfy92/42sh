/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 02:34:18 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_sigcont(t_jobs *jobs)
{
	t_jobs	*pipe;

	if (jobs->terminate == CLD_STOPPED)
	{
		if (kill (jobs->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	pipe = jobs->next_pipe;
	while (pipe)
	{
		if (pipe->terminate == CLD_STOPPED)
		{
			if (kill (pipe->pid, SIGCONT) < 0)
				perror ("kill (SIGCONT)");
		}
		pipe = pipe->next_pipe;
	}
	return (0);
}

int		check_jobs_enabled(t_group *grp, t_jobs *jobs)
{
	t_jobs	*pipe;
	t_jobs	*last;
	int stopped;
	int	count;

	stopped = 0;
	count = 1;
	if (jobs->terminate == CLD_EXITED || jobs->terminate == CLD_KILLED || 
		jobs->terminate == CLD_STOPPED)
		stopped += 1;
	last = jobs;
	pipe = jobs->next_pipe;
	while (pipe)
	{
		if (pipe->terminate == CLD_EXITED || pipe->terminate == CLD_KILLED ||
			pipe->terminate == CLD_STOPPED)
			stopped += 1;
		count++;
		last = pipe;
		pipe = pipe->next_pipe;
	}
	grp->exit = (last->code > 0) ? 1 : 0; 
	return (count == stopped ? false : true);
}

void	put_in_fg(t_group *grp, t_jobs *parent)
{
	if (grp)
		;
	tcsetpgrp(STDIN_FILENO, parent->pid);
	ft_sigcont(parent);
	while (42)
	{
		check_jobs_status(parent);
		if (check_jobs_enabled(grp, parent) == false)
			break ;
	}
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	grp->exit = parent->code;
}

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*curr;

	curr = get_jobs_idx(grp, idx);
	if (curr != NULL)
		put_in_fg(grp, curr);
	return (1);
}

int	builtin_bg(t_group *grp, int idx)
{
	t_jobs *curr;

	curr = get_jobs_idx(grp, idx);
	if (curr)
		ft_sigcont(curr);
	return (1);
}
