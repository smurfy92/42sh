/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:51:54 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/10 07:04:29 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	print l'env
*/

void	show_env(int choice, t_group *grp)
{
	t_envlst	*tmp;

	tmp = choice == 0 ? ENV(lst) : ENV(lst_tmp);
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putstr("=");
		ft_putendl(tmp->val);
		tmp = tmp->next;
	}
}

/*
**	initialise l'env tmp avec les value du current
*/

void	create_tmp_env(t_group *grp)
{
	t_envlst	*tmp;
	char		*var;
	char		*var_tmp;

	tmp = ENV(lst);
	while (tmp)
	{
		var = JOIN(tmp->name, "=");
		var_tmp = JOINF(var, tmp->val, 1);
		insert_env_tmp(grp, var_tmp);
		REMOVE(&var_tmp);
		tmp = tmp->next;
	}
}

static int		display_env_help(void)
{
	ft_putendl("usage: env [-i|-h] [name=value] [utility [argument]]");
	ft_putendl("env is used to create a copy of the current environment for a program.");
	ft_putendl("by using the pair name, value you can add env variables or change values of the existing ones.");
	ft_putendl("utility has to be an executable file.");
	ft_putendl("-i : remove all the env variables");
	ft_putendl("-h : display help");
	return (1);
}

/*
**	gestion de la builtin env -->
**	execute si necessaire && cree le tmp modifie
*/

int		builtin_env(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		start;
	int		end;

	cmdsplit = parse->cmdsplit;
	if (cmdsplit[1] && ft_strcmp(cmdsplit[1], "-h") == 0)
		return (display_env_help());
	if (env_opt(grp, parse) < 0 && !(cmdsplit[1] && ft_strcmp(cmdsplit[1], "-h") == 0))
		return ((grp->exit = 1));
	else if (ENV(opt_i) == false && ENV(start_varenv) == false && ENV(cmd) == NULL)
		show_env(0, grp);
	else
	{
		ENV(opt_i) == false ? create_tmp_env(grp) : 0;
		start = ENV(start_varenv);
		end = start + ENV(end_varenv);
		while (start < end)
		{
			insert_env_tmp(grp, cmdsplit[start]);
			start++;
		}
		ENV(cmd) == NULL ? show_env(1, grp) : init_exec_env(grp);
	}
	return (1);
}

/*
**	initialise l'environement si env -i
*/

void	init_env(t_group *grp, char **env)
{
	int		i;

	i = -1;
	while (env && env[++i])
		insert_env(grp, env[i]);
	ft_getenv(grp, "SHLVL") == NULL ? help_shlvl(grp) : shlvl(grp);
	if (ft_getenv(grp, "HOME") == NULL)
		home_helper(grp);
	if (ft_getenv(grp, "PATH") == NULL)
		path_help(grp);
	if (ft_getenv(grp, "PWD") == NULL)
		help_pwd(grp);
	if (ft_getenv(grp, "_") == NULL)
		under_helper(grp);
}
