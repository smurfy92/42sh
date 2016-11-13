/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/13 22:56:00 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_lstlen(t_envlst * envlst)
{
	int			i;
	t_envlst	*env;

	i = 0;
	env = envlst;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char		**list_to_tab(t_envlst *envlst)
{
	char		**env_tab;
	char		*tmp;
	int			pos;
	t_envlst	*env;

	pos = 0;
	env = envlst;
	env_tab = (char **)malloc(sizeof(char *) * (ft_lstlen(envlst) + 1));
	while (env != NULL)
	{
		tmp = JOIN(env->name, "=");
		env_tab[pos] = JOIN(tmp, env->val);
		pos++;
		env = env->next;
	}
	env_tab[pos] = NULL;
	return (env_tab);
}

char	*ft_getenv(t_group *grp, char *tofind)
{
	t_envlst	*env;

	env = grp->env->lst;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, tofind) == 0)
		{
			return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}

int		is_env(char *env)
{
	int i;

	i = -1;
	while (env[++i] != '\0')
	{
		if (env[i] == '=')
			break ;
	}
	if (env[i] != '=')
		return (false);
	return (i);
}
