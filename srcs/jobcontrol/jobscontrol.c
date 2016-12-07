/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobscontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:37:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/07 05:21:49 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

t_jobs		*control_jobs(t_jobs **parent, t_group *grp, t_parse *parse)
{
	static t_jobs	*jobs = NULL;
	t_jobs			*new;

	new = (t_jobs *)malloc(sizeof(t_jobs));
	new->next = NULL;
	new->next_pipe = NULL;
	new->enabled = true;
	if (*parent == NULL)
	{
		jobs = create_jobs(grp, new, parse->cmd, grp->father);
		*parent = jobs;
	}
	else
		jobs = create_pipe_jobs(new, jobs, parse->cmd, grp->father);
	return (jobs);

}

t_jobs		*get_jobs_idx(t_group *grp, int idx)
{
	t_jobs	*jobs;
	t_jobs	*curr;

	curr = NULL;
	jobs = grp->jobs;
	while (jobs)
	{
		curr = jobs;
		if (jobs && jobs->idx == idx)
			break;
		jobs = jobs->next;
	}
	if (curr == NULL || curr->pid < 0)
	{
		idx == 0 ? error_cmd("no jobs in background", "use & to create jobs", 1) :
		error_cmd("could not found jobs", ft_itoa(idx), 1);
		return (NULL);
	}
	return (curr);
}

t_jobs		*get_jobs_pid(t_group *grp, int pid)
{
	t_jobs	*jobs;
	t_jobs	*pipe;

	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs && jobs->pid == pid)
			return (jobs);
		pipe = jobs->next_pipe;
		while(pipe)
		{
			if (pipe && pipe->pid == pid)
				return (jobs);
			pipe = pipe->next_pipe;
		}
		jobs = jobs->next;
	}
	return (NULL);
}
