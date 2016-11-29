/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/30 00:07:08 by jmontija         ###   ########.fr       */
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
	// if (curr->code == SIGTSTP)
	// {
	// 	tcsetattr (STDIN_FILENO, 0, &curr->tmodes);
	// 	if (kill (- curr->pid, SIGCONT) < 0)
	// 		perror ("kill (SIGCONT)");
	// }
	tcsetpgrp (STDIN_FILENO, curr->pid);
	// pid_t pid;
	// pid = fork();
	// if (pid == 0)
	// {
	// 	tcsetpgrp (STDIN_FILENO, curr->pid);
	// 	ft_exit(grp, 0);
	// }
	waitpid(curr->pid, &ret, 0);
	//tcgetattr (STDIN_FILENO, &curr->tmodes);
	//tcsetpgrp(STDIN_FILENO, grp->program_pid);
	if (ret > 0)
		change_state(curr, ret);
	return (1);
}
