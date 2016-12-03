/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/03 06:26:13 by jmontija         ###   ########.fr       */
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

void	put_in_fg(t_group *grp, t_jobs *curr)
{
	int		ret;

	if (grp && curr == NULL)
		return ;
	tcsetpgrp (STDIN_FILENO, curr->pid);
	ft_sigcont(curr) ? change_state(curr, CLD_CONTINUED) : 0;
	//sleep(1);
	waitpid(curr->pid, &ret, 0);
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
}

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*curr;

	curr = get_jobs_idx(grp, idx);
	if (curr != NULL)
	{
		setpgid (grp->father, curr->pid);
		put_in_fg(grp, curr);
	}
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

int	builtin_jobs(t_group *grp)
{
	t_jobs	*tmp;

	tmp = grp->jobs;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			ft_putchar('[');
			ft_putnbr(tmp->idx);
			ft_putstr("] ");
			ft_putnbr(tmp->pid);
			ft_putchar(' ');
			ft_putstr(tmp->status);
			ft_putchar(' ');
			ft_putendl(tmp->cmd);
		}
		tmp = tmp->next;
	}
	jobs_update(grp);
	return (1);
}