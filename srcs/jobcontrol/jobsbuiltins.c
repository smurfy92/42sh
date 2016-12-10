/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/10 05:01:37 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_sigcont(t_jobs *jobs)
{
	t_jobs	*pipe;

	if (jobs->terminate == SIGNSTOP)
	{
		if (kill (jobs->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	pipe = jobs->next_pipe;
	while (pipe)
	{
		if (pipe->terminate == SIGNSTOP)
		{
			if (kill (pipe->pid, SIGCONT) < 0)
				perror ("kill (SIGCONT)");
		}
		pipe = pipe->next_pipe;
	}
	return (0);
}

int		check_jobs_stopped(t_group *grp, t_jobs *jobs)
{
	t_jobs	*pipe;
	t_jobs	*last;

	if (jobs == NULL)
		return (true);
	if (jobs->enabled == true)
		return (false);
	last = jobs;
	pipe = jobs->next_pipe;
	while (pipe)
	{
		if (pipe->enabled == true)
			return (false);
		last = pipe;
		pipe = pipe->next_pipe;
	}
	grp->exit = (last->code > 0 && last->terminate != SIGNSTOP) ? 1 : 0; 
	return (true);
}

void	put_in_fg(t_group *grp, t_jobs *pgid)
{
	tcsetpgrp(STDIN_FILENO, pgid->pid);
	ft_sigcont(pgid);
	while (42)
	{
		if (check_group_status(pgid, 0) < 0 || check_jobs_stopped(grp, pgid))
			break ;
	}
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
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
