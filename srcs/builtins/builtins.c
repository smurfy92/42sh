/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/26 01:21:23 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int	is_builtins(char **cmd)
{
	if (!cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "history") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "jobs") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "fg") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "bg") == 0)
		return (1);
	return (0);
}

int	builtin_setenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	cmdsplit[1] == NULL ? error_cmd("setenv", "no argument given", 1) : 0;
	while (cmdsplit[++i] != NULL)
	{
		if (!ft_strncmp(cmdsplit[i], "_", 1) ||
			!ft_strncmp(cmdsplit[i], "SHLVL", 5))
		{
			error_cmd("setenv: 'SHLVL'", "'_' can't be modify", 1);
			return (1);
		}
		else if (insert_env(grp, cmdsplit[i]) < 0)
		{
			error_cmd("setenv: bad syntax", cmdsplit[i], 1);
			return (1);
		}
	}
	return (1);
}

int	builtin_unsetenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	cmdsplit[1] == NULL ? error_cmd("unsetenv", "no argument given", 1) : 0;
	while (cmdsplit[++i] != NULL)
	{
		if (!ft_strncmp(cmdsplit[i], "_", 1) ||
			!ft_strncmp(cmdsplit[i], "SHLVL", 5))
		{
			error_cmd("unsetenv: 'SHLVL'", "'_' can't be modify", 1);
			return (1);
		}
		else if (unset_env(grp, cmdsplit[i]) < 0)
		{
			error_cmd("unsetenv: unfound key", cmdsplit[i], 1);
			return (1);
		}
	}
	return (1);
}

int	builtin_next(t_group *grp, t_parse *parse, char **cmd)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ret = builtin_unsetenv(grp, parse);
	else if (ft_strcmp(cmd[0], "history") == 0)
		ret = builtin_history(grp, parse);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ret = builtin_echo(grp, parse);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(grp, (cmd[1] != NULL ? ft_atoi(cmd[1]) : grp->exit));
	else if (ft_strcmp(cmd[0], "jobs") == 0)
		ret = builtin_jobs(grp);
	else if (ft_strcmp(cmd[0], "fg") == 0)
		ret = builtin_fg(grp, (cmd[1] != NULL ? ft_atoi(cmd[1]) : 0));
	else if (ft_strcmp(cmd[0], "bg") == 0)
		ret = builtin_bg();
	return (ret);
}

/*
**	exit code to do for history et echo ??
*/

int	builtins(t_group *grp, t_parse *parse)
{
	int		ret;
	char	**cmd;

	ret = 0;
	cmd = parse->cmdsplit;
	if (!cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "env") == 0)
		ret = builtin_env(grp, parse);
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if ((cmd[1] && ft_strcmp(cmd[1], ".") == 0) ||
			(cmd[1] && ft_strcmp(cmd[1], ".") == 0))
			return ((ret = 0));
		ret = builtin_cd(grp, parse);
	}
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ret = builtin_setenv(grp, parse);
	else
		return (builtin_next(grp, parse, cmd));
	return (ret);
}
