/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 00:53:40 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/14 19:19:53 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static int		isvalid_opt(t_group *grp, char opt, int *options, char *envopt)
{
	size_t	i;

	i = -1;
	while (grp && ++i < LEN(envopt))
	{
		if (opt == envopt[i])
		{
			opt == '-' ? (options[0] = true) : 0;
			opt == 'l' ? (options[1] = true) : 0;
			opt == 'p' ? (options[2] = true) : 0;
			return (1);
		}
	}
	return (-1);
}

static int		analyse_opt(t_group *grp, char *arg, int *options, char *envopt)
{
	size_t	i;

	i = 0;
	if (arg[1] == '\0')
		isvalid_opt(grp, '-', options, envopt);
	while (++i < LEN(arg))
	{
		if (isvalid_opt(grp, arg[i], options, envopt) < 0)
		{
			free(envopt);
			error_cmd("jobs", "bad options", 1);
			return (-1);
		}
	}
	return (1);
}

int				jobs_opt(t_group *grp, char **cmd, int *options)
{
	int		i;
	int		is_jobs;
	char	*envopt;
	t_jobs	*jobs;

	i = 0;
	envopt = SDUP("-lp");
	is_jobs = false;
	while (cmd && cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			if (analyse_opt(grp, cmd[i], options, envopt) < 0)
				return (-1);
		}
		else
		{
			jobs = get_jobs_idx(grp, ft_atoi(cmd[i]));
			jobs ? display_pgid(jobs, options) : 0;
			is_jobs = true;
		}
	}
	REMOVE(&envopt);
	return (is_jobs ? -1 : 0);
}

int				builtin_jobs(t_group *grp, char **cmd)
{
	t_jobs	*jobs;
	int		options[3];

	options[0] = false;
	options[1] = false;
	options[2] = false;
	if (jobs_opt(grp, cmd, options) < 0)
		return (1);
	jobs = grp->jobs;
	while (jobs)
	{
		display_pgid(jobs, options);
		jobs = jobs->next;
	}
	return (1);
}
