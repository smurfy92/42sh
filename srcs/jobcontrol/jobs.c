/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:26 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/26 01:21:18 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int	builtin_jobs(t_group *grp)
{
	t_jobs	*tmp;

	tmp = grp->jobs;
	while (tmp)
	{
		printf("[%d] %d %s\n", tmp->idx, tmp->pid, tmp->cmd);
		tmp = tmp->next;
	}
	return (1);
}