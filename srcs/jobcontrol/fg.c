/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:24:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/01 02:18:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	put_in_fg(t_group *grp, t_jobs *curr)
{
	int		ret;

	tcsetpgrp (STDIN_FILENO, curr->pid);
	// if (curr->code == SIGTSTP)
	// {
	// 	tcsetattr (STDIN_FILENO, 0, &curr->tmodes);
	// 	if (kill (- curr->pid, SIGCONT) < 0)
	// 		perror ("kill (SIGCONT)");
	// }
	waitpid(curr->pid, &ret, WUNTRACED);
	//printf("ST: %d\nSRET: %d\nWRET: %d\n", WIFSIGNALED(ret), WEXITSTATUS(ret), WSTOPSIG(ret));
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	tcgetattr(STDIN_FILENO, &curr->tmodes);
	error_process_check(ret);
	change_state(curr, WEXITSTATUS(ret));
	grp->exit = (ret > 0 ? 1 : 0);
}

int		builtin_fg(t_group *grp, int idx)
{
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
	setpgid (grp->father, curr->pid);
	put_in_fg(grp, curr);
	return (1);
}
