/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 00:53:40 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/10 08:15:50 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static int		isvalid_opt(t_group *grp, char opt, int *options, char *env_options)
{
	size_t	i;

	i = -1;
	while (grp && ++i < LEN(env_options))
	{
		if (opt == env_options[i])
		{
			opt == '-' ? (options[0] = true) : 0 ;
			opt == 'l' ? (options[1] = true) : 0 ;
			opt == 'p' ? (options[2] = true) : 0 ;
			return (1);
		}
	}
	return (-1);
}

static int		analyse_opt(t_group *grp, char *arg, int *options, char *env_options)
{
	size_t	i;

	i = 0;
	if (arg[1] == '\0')
		isvalid_opt(grp, '-', options, env_options);
	while (++i < LEN(arg))
	{
		if (isvalid_opt(grp, arg[i], options, env_options) < 0)
			return (-1);
	}
	return (1);
}


void	display_jobs_pipe(t_jobs *jobs, int *options)
{	
	t_jobs	*pipe;

	ft_putchar('\n');
	pipe = jobs->next_pipe;
	while(options[1] && pipe)
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

int		jobs_opt(t_group *grp, char **cmd, int *options)
{
	int		i;
	int		is_jobs;
	char	*env_options;
	t_jobs	*jobs;

	i = 0;
	env_options = SDUP("-lp");
	is_jobs = false;
	while (cmd && cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			if (analyse_opt(grp, cmd[i], options, env_options) < 0)
			{
				REMOVE(&env_options);
				error_cmd("jobs", "bad options", 1);
				return (-1);
			}
		}
		else
		{
			jobs = get_jobs_idx(grp, ft_atoi(cmd[i]));
			if (jobs)
				display_jobs(jobs, 1, 1);
			is_jobs = true;
		}
	}
	REMOVE(&env_options);
	return (is_jobs ? -1 : 0);
}

int	builtin_jobs(t_group *grp, char **cmd)
{
	t_jobs	*tmp;
	int		options[3];

	options[0] = false;
	options[1] = false;
	options[2] = false;
	if (jobs_opt(grp, cmd, options) < 0)
		return (1);
	tmp = grp->jobs;
	while (tmp)
	{
		if (options[2])
			ft_putnbr(tmp->pid);
		else if (options [1])
			display_jobs(tmp, 0, 0);
		else
			display_jobs(tmp, 0, 1);
		display_jobs_pipe(tmp, options);
		check_group_status(tmp, 1);
		tmp = tmp->next;
	}
	return (1);
}
