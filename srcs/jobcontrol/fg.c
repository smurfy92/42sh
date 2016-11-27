/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/28 00:04:35 by jmontija         ###   ########.fr       */
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
	if (curr == NULL)
	{
		idx == 0 ? error_cmd("no jobs in background", "use & to create jobs", 1) :
		error_cmd("could not found jobs", ft_itoa(idx), 1);
		return (1);
	}

	//reset_shell();
	tcsetpgrp (STDIN_FILENO, curr->pid);

	// if (cont)
	//   {
	//     tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
	//     if (kill (- j->pgid, SIGCONT) < 0)
	//       perror ("kill (SIGCONT)");
	//   }
	
	waitpid(curr->pid, &ret, 0);
	tcsetpgrp (STDIN_FILENO, grp->program_pid);
	printf("\nend of processus fg\n");
	return (1);
}