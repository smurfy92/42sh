/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/11 05:59:19 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_sigcont(t_jobs *jobs)
{
	t_jobs	*pipe;

	pipe = jobs;
	while (pipe)
	{
		if (pipe->terminate == SIGNSTOP)
		{
			tcsetattr(STDIN_FILENO, 0, &pipe->tmodes);
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
	last = jobs;
	pipe = jobs;
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
	reset_shell();
	tcsetpgrp(STDIN_FILENO, pgid->pid);
	ft_sigcont(pgid);
	while (42)
	{
		if (check_group_status(pgid, 0) < 0 || check_jobs_stopped(grp, pgid))
			break ;
	}
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	restore_shell();
}

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*curr;

	idx == 0 ? (idx = -1) : 0;
	curr = get_jobs_idx(grp, idx);
	if (curr != NULL)
		put_in_fg(grp, curr);
	return (1);
}

int	builtin_bg(t_group *grp, int idx)
{
	t_jobs *curr;

	idx == 0 ? (idx = -1) : 0;
	curr = get_jobs_idx(grp, idx);
	if (curr)
		ft_sigcont(curr);
	return (1);
}
