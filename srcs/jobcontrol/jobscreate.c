/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobscreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 23:41:24 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 01:06:04 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		display_jobs(t_jobs *jobs, int n)
{
	if (jobs == NULL)
		return ;
	!jobs->idx ? ft_putstr_fd("  ", 1) : 0;
	ft_putstr_fd("[", 1);
	!jobs->idx ? ft_putchar_fd('p', 1) : ft_putnbr_fd(jobs->idx, 1);
	ft_putstr_fd("] ", 1);
	ft_putnbr_fd(jobs->pid, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(jobs->status, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(jobs->cmd, 1);
	if (n)
		ft_putchar_fd('\n', 1);
}

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = SDUP("RUNNING");
	jobs->cmd = SDUP(cmd);
	jobs->terminate = -1;
	jobs->code = 0;
}

t_jobs		*create_jobs(t_group *grp, t_jobs *new, char *cmd, int pid)
{
	t_jobs		*tmp;
	int			count;

	count = 2;
	fill_jobs(new, 1, pid, cmd);
	if (!grp->jobs)
		grp->jobs = new;
	else
	{
		tmp = grp->jobs;
		while (tmp && (tmp->next || tmp->pid == -1))
		{
			count++;
			if (tmp->pid == -1)
			{
				REMOVE(&new->cmd); free(new);
				fill_jobs(tmp, tmp->idx, pid, cmd);
				return (tmp);
			}
			tmp = tmp->next;
		}
		tmp->next = new;
		tmp->next->idx = count;
	}
	return(new);
}

t_jobs		*create_pipe_jobs(t_jobs *new, t_jobs *jobs, char *cmd, int pid)
{
	new->idx = 0;
	new->pid = pid;
	new->status = SDUP("RUNNING");
	new->cmd = SDUP(cmd);
	new->terminate = -1;
	jobs->next_pipe = new;
	jobs->code = 0;
	return(new);
}
