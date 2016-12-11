/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:51:54 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/11 16:28:40 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	print l'env
*/

void			show_env(int choice, t_group *grp)
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

void			create_tmp_env(t_group *grp)
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
	ft_putstr("env is used to create a copy of the current");
	ft_putendl(" environment for a program.");
	ft_putstr("by using the pair name, value you can add env vari");
	ft_putendl("ables or change values of the existing ones.");
	ft_putendl("utility has to be an executable file.");
	ft_putendl("-i : remove all the env variables");
	ft_putendl("-h : display help");
	return (1);
}

/*
**	gestion de la builtin env -->
**	execute si necessaire && cree le tmp modifie
*/

int				builtin_env(t_group *grp, t_parse *parse)
{
	char	**cmdsp;
	int		start;
	int		end;

	cmdsp = parse->cmdsplit;
	if (cmdsp[1] && ft_strcmp(cmdsp[1], "-h") == 0)
		return (display_env_help());
	if (env_opt(grp, parse) < 0 && !(cmdsp[1] && CMP(cmdsp[1], "-h") == 0))
		return ((grp->exit = 1));
	else if (ENV(opt_i) == false && ENV(start_varenv) == false
		&& ENV(cmd) == NULL)
		show_env(0, grp);
	else
	{
		ENV(opt_i) == false ? create_tmp_env(grp) : 0;
		start = ENV(start_varenv);
		end = start + ENV(end_varenv);
		while (start < end)
		{
			insert_env_tmp(grp, cmdsp[start]);
			start++;
		}
		ENV(cmd) == NULL ? show_env(1, grp) : init_exec_env(grp);
	}
	return (1);
}

/*
**	initialise l'environement si env -i
*/

void			init_env(t_group *grp, char **env)
{
	int		i;

	i = -1;
	while (env && env[++i])
		insert_env(grp, env[i]);
	if (!ft_getenv(grp, "SHLVL"))
		insert_env(grp, "SHLVL=1");
	else
		shlvl(grp);
	if (ft_getenv(grp, "HOME") == NULL)
		home_helper(grp);
	if (ft_getenv(grp, "PATH") == NULL)
		path_help(grp);
	if (ft_getenv(grp, "PWD") == NULL)
		help_pwd(grp);
	if (ft_getenv(grp, "_") == NULL)
		under_helper(grp);
}
