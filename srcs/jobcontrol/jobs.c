/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:26 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/28 00:03:07 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int	builtin_jobs(t_group *grp)
{
	t_jobs	*tmp;

	jobs_status(grp); // ce jobs_status doit changer les params pour l'affichage (jobs_states)
	tmp = grp->jobs;
	while (tmp)
	{
		if (tmp->pid > 0)
			printf("[%d] %d %s\n", tmp->idx, tmp->pid, tmp->cmd);
		tmp = tmp->next;
	}
	//jobs_status(grp); // ce jobs_status doit clear les jobs done or else ! (jobs_update)
	return (1);
}