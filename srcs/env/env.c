/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:51:54 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 17:01:39 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	show_env(int choice, t_group *grp)
{
	t_envlst	*tmp;

	tmp = choice == 0 ? ENV(lst) : ENV(lst_tmp);
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putstr("="
			);
		ft_putendl(tmp->val);
		tmp = tmp->next;
	}
}

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

int		builtin_env(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;
	int		start;
	int		end;

	cmdsplit = parse->cmdsplit;
	if (env_opt(grp) < 0)
		return (-1);
	if (ENV(opt_i) == false && ENV(start_varenv) == false && ENV(cmd) == NULL)
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
