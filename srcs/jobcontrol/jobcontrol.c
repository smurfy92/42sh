/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:18:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/01 02:07:38 by jmontija         ###   ########.fr       */
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

t_jobs		*display_jobs(int idx, int pid)
{
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(idx, 2);
	ft_putstr_fd("] ", 2);
	ft_putnbr_fd(pid, 2);
	ft_putchar('\n');
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
				display_jobs(tmp2->idx, pid);
				return (tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp2->next = tmp;
		tmp2->next->idx = count;
	}
	display_jobs(tmp->idx, pid);
	return(tmp);
}
