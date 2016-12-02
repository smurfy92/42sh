/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/02 05:08:16 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	ft_sigcont(t_jobs *curr)
{
	if (curr->terminate == SIGTSTP)
	{
		if (kill (-curr->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
}

void	put_in_fg(t_group *grp, t_jobs *curr)
{
	int		ret;
	int		code;

	if (curr == NULL)
		return ;
	tcsetpgrp (STDIN_FILENO, curr->pid);
	ft_sigcont(curr);
	waitpid(curr->pid, &ret, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	code = WEXITSTATUS(ret) ? WEXITSTATUS(ret) : ret;
	change_state(curr, code);
	grp->exit = (code > 0 ? 1 : 0);
}

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*curr;

	curr = get_jobs(grp, idx);
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

	curr = get_jobs(grp, idx);
	if (curr)
		ft_sigcont(curr);
	return (1);
}

int	builtin_jobs(t_group *grp)
{
	t_jobs	*tmp;

	jobs_states(grp);
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