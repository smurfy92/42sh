/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/10/30 18:44:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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
