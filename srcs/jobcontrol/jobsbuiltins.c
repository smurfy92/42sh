/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/07 04:53:20 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_sigcont(t_jobs *curr)
{
	if (curr->terminate == CLD_STOPPED)
	{
		if (kill (-curr->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		return (1);
	}
	return (0);
}

void	put_in_fg(t_group *grp, t_jobs *parent)
{
	if (grp)
		;
	tcsetpgrp(STDIN_FILENO, parent->pid);
	ft_sigcont(parent) ? change_state(parent, CLD_CONTINUED) : 0;
	while (42) 
	{
		if (parent->terminate > -1 && parent->terminate != CLD_CONTINUED)
		{
			// here check the pipe to get back the hand
			printf("parent_terrminate: %d\n", parent->terminate);
			break ;
		}
	}
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	//grp->exit = (parent->terminate > 1 && parent->terminate != CLD_CONTINUED && parent->terminate != CLD_STOPPED ? 1 : 0);
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
