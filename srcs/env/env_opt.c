/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:18:52 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 06:25:14 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		isvalid_opt(t_group *grp, char opt)
{
	size_t	i;
	char	*env_options;

	i = -1;
	env_options = SDUP("-i");
	while (++i < LEN(env_options))
	{
		if (opt == env_options[i])
		{
			ENV(opt_i) = true;
			REMOVE(&env_options);
			return (1);
		}
	}
	REMOVE(&env_options);
	return (error_env_opt(opt, " illegal option -- "));
}

int		analyse_opt(t_group *grp, char *arg)
{
	size_t	i;

	i = 0;
	if (arg[1] == '\0')
		isvalid_opt(grp, '-');
	while (++i < LEN(arg))
	{
		if (isvalid_opt(grp, arg[i]) < 0)
			return (-1);
	}
	return (1);
}

int		env_cmd(t_group *grp, char *env_cmd)
{
	if (ENV(cmd))
	{
		ENV(cmd) = JOINF(ENV(cmd), " ", 1);
		ENV(cmd) = JOINF(ENV(cmd), env_cmd, 1);
	}
	else
		ENV(cmd) = SDUP(env_cmd);
	return (3);
}

int		env_opt(t_group *grp, t_parse *parse)
{
	int		i;
	int		step;

	i = 0;
	step = 0;
	while (parse->cmdsplit && parse->cmdsplit[++i])
	{
		if (parse->cmdsplit[i][0] == '-' && step <= 1)
		{
			step = 1;
			if (analyse_opt(grp, parse->cmdsplit[i]) < 0)
				return (-1);
		}
		else if (is_env(parse->cmdsplit[i]) > 0)
		{
			if (step < 2)
				ENV(start_varenv) = i;
			(ENV(end_varenv)) += 1;
			step = 2;
		}
		else
			step = env_cmd(grp, parse->cmdsplit[i]);
	}
	return (0);
}
