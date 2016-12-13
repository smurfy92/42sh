/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobscontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:37:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 15:54:20 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		display_jobs(t_jobs *jobs, int n, int parent)
{
	t_group	*grp;

	grp = get_grp();
	if (jobs == NULL || grp->is_interact == false)
		return ;
	!jobs->idx ? ft_putstr_fd("  ", 1) : 0;
	ft_putstr_fd("[", 1);
	!jobs->idx ? ft_putchar_fd('p', 1) : ft_putnbr_fd(jobs->idx, 1);
	ft_putstr_fd("] ", 1);
	ft_putnbr_fd(jobs->pid, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(jobs->status, 1);
	ft_putchar_fd(' ', 1);
	parent ? ft_putstr_fd(jobs->parent_cmd, 1) : ft_putstr_fd(jobs->cmd, 1);
	if (n)
		ft_putchar_fd('\n', 1);
}

t_jobs		*control_jobs(t_jobs **parent, t_group *grp, char *cmd, char *pcmd)
{
	static t_jobs	*jobs = NULL;
	t_jobs			*new;

	new = (t_jobs *)malloc(sizeof(t_jobs));
	new->next = NULL;
	new->next_pipe = NULL;
	new->enabled = true;
	if (*parent == NULL)
	{
		jobs = create_jobs(grp, new, cmd, grp->father);
		jobs->parent_cmd = SDUP(pcmd);
		*parent = jobs;
	}
	else
		jobs = create_pipe_jobs(new, jobs, cmd, grp->father);
	return (jobs);
}

t_jobs		*get_jobs_idx(t_group *grp, int idx)
{
	t_jobs	*jobs;
	t_jobs	*curr;
	t_jobs	*last;

	curr = NULL;
	last = NULL;
	jobs = grp->jobs;
	while (jobs)
	{
		last = jobs;
		if (jobs && jobs->idx == idx)
		{
			curr = jobs;
			break ;
		}
		jobs = jobs->next;
	}
	(idx == -1 && last) ? (curr = last) : 0;
	if (curr == NULL)
	{
		idx == -1 ? (idx = 0) : 0;
		error_cmd("could not found jobs", "42sh", 1);
		return (NULL);
	}
	return (curr);
}

t_jobs		*get_jobs_pid(int pid)
{
	t_jobs	*jobs;
	t_jobs	*pipe;
	t_group *grp;

	grp = get_grp();
	jobs = grp->jobs;
	while (jobs)
	{
		pipe = jobs;
		while (pipe)
		{
			if (pipe && pipe->pid == pid)
				return (pipe);
			pipe = pipe->next_pipe;
		}
		jobs = jobs->next;
	}
	return (NULL);
}
