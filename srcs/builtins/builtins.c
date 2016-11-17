/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 19:46:07 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int	is_builtins(char **cmd)
{
	if (!cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1); // exit code done
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1); // exit code done
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (1); // exit code done
	else if (ft_strcmp(cmd[0], "history") == 0)
		return (1); // exit code done
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1); // exit code done
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1); // exit code done
	return (0);
}

int	builtin_setenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	t_bool	error;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	error = cmdsplit[1] != NULL ? false : true;
	while (cmdsplit[++i] != NULL)
	{
		if (!ft_strncmp(cmdsplit[i], "_", 1) ||
			!ft_strncmp(cmdsplit[i], "SHLVL", 5))
		{
			ft_putendl_fd("setenv: \"SHLVL\" and \"_\" can't be modify", 2);
			break ;
		}
		else if (insert_env(grp, cmdsplit[i]) < 0)
		{
			ft_putstr_fd("setenv: bad synthax -> ", 2);
			ft_putendl_fd(cmdsplit[i], 2);
			error = true;
		}
	}
	grp->exit = error ? 1 : 0;
	return (1);
}

int	builtin_unsetenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	t_bool	error;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	error = cmdsplit[1] != NULL ? false : true;
	while (cmdsplit[++i] != NULL)
	{
		if (!ft_strncmp(cmdsplit[i], "_", 1) ||
			!ft_strncmp(cmdsplit[i], "SHLVL", 5))
		{
			ft_putendl_fd("setenv: 'SHLVL', '_' can't be modify", 2);
			break ;
		}
		else if (unset_env(grp, cmdsplit[i]) < 0)
		{
			ft_putstr_fd("unsetenv: unfound key -> ", 2);
			ft_putendl_fd(cmdsplit[i], 2);
			error = true;
		}
	}
	grp->exit = error ? 1 : 0;
	return (1);
}

int	builtins(t_group *grp, t_parse *parse)
{
	int		ret;
	char	**cmd;

	ret = 0;
	cmd = parse->cmdsplit;
	if (!cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "env") == 0)
		ret = builtin_env(grp, parse); // exit code done
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ret = builtin_cd(grp, parse); // exit code done
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ret = builtin_setenv(grp, parse); // exit code done
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ret = builtin_unsetenv(grp, parse); // exit code done
	else if (ft_strcmp(cmd[0], "history") == 0)
		ret = builtin_history(grp, parse);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ret = builtin_echo(grp, parse);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(grp, (cmd[1] != NULL ? ft_atoi(cmd[1]) : grp->exit));
	return (ret);
}
