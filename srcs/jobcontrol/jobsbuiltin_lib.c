/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltin_lib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:29:37 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 16:33:51 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	display_pipe(t_jobs *jobs, int *options)
{
	t_jobs	*pipe;

	ft_putchar('\n');
	pipe = jobs->next_pipe;
	while (options[1] && pipe)
	{
		if (options[2])
		{
			ft_putstr("  ");
			ft_putnbr(pipe->pid);
			ft_putchar('\n');
		}
		else
			display_jobs(pipe, 1, 0);
		pipe = pipe->next_pipe;
	}
}

void	display_pgid(t_jobs *jobs, int *options)
{
	if (jobs == NULL)
		return ;
	if (options[2])
		ft_putnbr(jobs->pid);
	else if (options[1])
		display_jobs(jobs, 0, 0);
	else
		display_jobs(jobs, 0, 1);
	display_pipe(jobs, options);
	check_group_status(jobs, 1);
}
