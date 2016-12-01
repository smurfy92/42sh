/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/01 05:26:14 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int	builtin_bg(t_group *grp, int idx)
{
	// t_jobs *curr;

	// //curr = get_jobs(grp, idx);
	t_jobs	*jobs;
	t_jobs	*curr;

	curr = NULL;
	jobs = grp->jobs;
	while (jobs)
	{
		if (jobs->idx == idx)
		{
			curr = jobs;
			break;
		}
		jobs = jobs->next;
	}
	if (idx == 0)
		curr = jobs;
	if (curr == NULL || curr->pid < 0)
	{
		idx == 0 ? error_cmd("no jobs in background", "use & to create jobs", 1) :
		error_cmd("could not found jobs", ft_itoa(idx), 1);
		return (1);
	}
	if (curr->terminate == SIGTSTP)
	{
		//tcsetattr (STDIN_FILENO, 0, &curr->tmodes);
		if (kill (-curr->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	return (1);
}
