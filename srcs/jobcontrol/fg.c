/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 05:18:37 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*jobs;
	t_jobs	*curr;
	int		ret;

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
	tcsetpgrp (STDIN_FILENO, curr->pid);
	// if (cont)
	//   {
	//     tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
	//     if (kill (- j->pgid, SIGCONT) < 0)
	//       perror ("kill (SIGCONT)");
	//   }
	waitpid(curr->pid, &ret, 0);
	if (ret > 0)
		change_state(curr, ret);
	return (1);
}