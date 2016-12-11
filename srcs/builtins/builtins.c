/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/11 16:09:50 by vdanain          ###   ########.fr       */
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
		ret = builtin_jobs(grp, cmd);
	else if (ft_strcmp(cmd[0], "fg") == 0)
		ret = builtin_fg(grp, (cmd[1] != NULL ? ft_atoi(cmd[1]) : 0));
	else if (ft_strcmp(cmd[0], "bg") == 0)
		ret = builtin_bg(grp, (cmd[1] != NULL ? ft_atoi(cmd[1]) : 0));
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
