/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobscreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:37:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/03 04:33:36 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		fill_jobs(t_jobs *jobs, int idx, int pid, char *cmd)
{
	jobs->idx = idx;
	jobs->pid = pid;
	jobs->status = SDUP("RUNNING");
	jobs->cmd = SDUP(cmd);
	jobs->is_last = true;
	jobs->is_prelast = false;
	jobs->terminate = -1;
}

t_jobs		*display_jobs(int idx, int pid, int n)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(idx, 2);
	ft_putstr_fd("] ", 2);
	ft_putnbr_fd(pid, 2);
	if (n)
		ft_putchar_fd('\n', 2);
	return (NULL);
}

t_jobs		*create_jobs(t_group *grp, char *cmd, int pid)
{
	t_jobs		*tmp;
	t_jobs		*tmp2;
	int			count;

	count = 2;
	tmp = (t_jobs *)malloc(sizeof(t_jobs));
	tmp->next = NULL;
	fill_jobs(tmp, 1, pid, cmd);
	if (!grp->jobs)
		grp->jobs = tmp;
	else
	{
		tmp2 = grp->jobs;
		while (tmp2 && (tmp2->next || tmp2->pid == -1))
		{
			count++;
			if (tmp2->pid == -1)
			{
				REMOVE(&tmp->cmd); free(tmp);
				fill_jobs(tmp2, tmp2->idx, pid, cmd);
				display_jobs(tmp2->idx, pid, 1);
				return (tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp2->next = tmp;
		tmp2->next->idx = count;
	}
	display_jobs(tmp->idx, pid, 1);
	return(tmp);
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
		if (jobs->idx == idx)
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
	t_jobs	*curr;

	curr = NULL;
	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs->pid == pid)
		{
			curr = jobs;
			break;
		}
		jobs = jobs->next;
	}
	if (curr == NULL || curr->pid < 0)
		return (NULL);
	return (curr);
}
