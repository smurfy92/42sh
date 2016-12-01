/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:26 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/30 04:40:19 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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