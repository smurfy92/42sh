/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobscreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 23:41:24 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 10:24:39 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		free_jobs(t_jobs *jobs)
{
	t_jobs	*pipe;
	t_jobs	*next;

	REMOVE(&jobs->status);
	REMOVE(&jobs->cmd);
	REMOVE(&jobs->parent_cmd);
	pipe = jobs->next_pipe;
	while (pipe)
	{
		next = pipe->next_pipe;
		REMOVE(&pipe->status);
		REMOVE(&pipe->cmd);
		free(pipe);
		pipe = NULL;
		pipe = next;
	}
	free(jobs);
	jobs = NULL;
}

void		remove_jobs(int pgid)
{
	t_jobs		*jobs;
	t_jobs		*next;
	t_jobs		*prev;
	t_group		*grp;

	prev = NULL;
	grp = get_grp();
	jobs = grp->jobs;
	while (jobs)
	{
		next = jobs->next;
		if (pgid == jobs->pid)
		{
			if (prev)
				prev->next = next;
			else if (prev == NULL && next != NULL)
				grp->jobs = next;
			else if (prev == NULL && next == NULL)
				grp->jobs = NULL;
			free_jobs(jobs);
			return ;
		}
		prev = jobs;
		jobs = next;
	}
}

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = SDUP("running");
	jobs->cmd = SDUP(cmd);
	jobs->terminate = -1;
	jobs->code = 0;
	jobs->fg = false;
}

t_jobs		*create_jobs(t_group *grp, t_jobs *new, char *cmd, int pid)
{
	t_jobs		*tmp;

	fill_jobs(new, 1, pid, cmd);
	if (!grp->jobs)
		grp->jobs = new;
	else
	{
		tmp = grp->jobs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		new->idx = tmp->idx + 1;
		tmp->next = new;
	}
	return (new);
}

t_jobs		*create_pipe_jobs(t_jobs *new, t_jobs *jobs, char *cmd, int pid)
{
	new->idx = 0;
	new->pid = pid;
	new->status = SDUP("running");
	new->cmd = SDUP(cmd);
	new->terminate = -1;
	new->parent_cmd = NULL;
	new->fg = false;
	new->code = 0;
	jobs->next_pipe = new;
	return (new);
}
