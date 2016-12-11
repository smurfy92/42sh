/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_set_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 16:09:03 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 16:13:11 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		display_setenv_help(void)
{
	ft_putendl("usage: setenv [-h] [name=value]");
	ft_putendl("setenv is used to set or modify an environment variable");
	ft_putendl("-h : display help");
}

int				builtin_setenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	cmdsplit[1] == NULL ? error_cmd("setenv", "no argument given", 1) : 0;
	if (ft_strcmp(cmdsplit[1], "-h") == 0)
		display_setenv_help();
	while (cmdsplit[++i] != NULL && ft_strcmp(cmdsplit[i], "-h"))
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

static void		display_unsetenv_help(void)
{
	ft_putendl("usage : unsetenv [-h] [ name ]");
	ft_putstr("unsetenv is used to unset an environment");
	ft_putendl(" variable in your current shell");
	ft_putendl("-h : display help");
}

int				builtin_unsetenv(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		i;

	i = 0;
	cmdsplit = parse->cmdsplit;
	cmdsplit[1] == NULL ? error_cmd("unsetenv", "no argument given", 1) : 0;
	if (ft_strcmp(cmdsplit[1], "-h") == 0)
		display_unsetenv_help();
	while (cmdsplit[++i] != NULL && ft_strcmp(cmdsplit[1], "-h"))
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
