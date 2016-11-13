/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 15:44:38 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/13 01:49:48 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				unset_env_tmp(t_group *grp, char *todel)
{
	t_envlst *curr;
	t_envlst *prev;

	prev = NULL;
	curr = grp->env->lst_tmp;
	ft_strcmp(todel, "_") == 0 ? todel = NULL : 0;
	ft_strcmp(todel, "SHLVL") == 0 ? todel = NULL : 0;
	while (todel != NULL && curr != NULL)
	{
		if ((ft_strcmp(curr->name, todel) == 0))
		{
			if (prev == NULL)
				grp->env->lst_tmp = curr->next;
			else
				prev->next = curr->next;
			REMOVE(&curr->name);
			REMOVE(&curr->val);
			ft_memdel((void *)&curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (-1);
}

static t_envlst	*create_env_line(t_group *grp, char *env, int i)
{
	t_envlst *new;
	t_envlst *curr_env;

	curr_env = grp->env->lst_tmp;
	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!(new) || !(env))
		return (NULL);
	if ((i = is_env(env)) == false)
		return (NULL);
	new->exist = false;
	new->name = SUB(env, 0, i);
	new->val = SUB(env, i + 1, LEN(env));
	while (curr_env != NULL)
	{
		if (ft_strcmp(new->name , "PATH") == 0)
			ENV(path_tmp) = SDUP(new->val);
		if (ft_strcmp(new->name, curr_env->name) == 0)
		{
			new->exist = true;
			REMOVE(&curr_env->val);
			curr_env->val = ft_strdup(new->val);
			return (new);
		}
		curr_env = curr_env->next;
	}
	new->next = NULL;
	return (new);
}

static int		free_and_return(t_envlst *new)
{
	REMOVE(&new->val);
	REMOVE(&new->name);
	free(new);
	new = NULL;
	return (1);
}

int				insert_env_tmp(t_group *grp, char *env)
{
	t_envlst	*new;
	t_envlst	*tmp;
	char		*tmp2;
	int			i;

	i = 0;
	tmp = grp->env->lst_tmp;
	tmp2 = ft_strtrim(env);
	new = create_env_line(grp, tmp2, i);
	REMOVE(&tmp2);
	if (new == NULL)
		return (-1);
	if (new->exist == true)
		return (free_and_return(new));
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		grp->env->lst_tmp = new;
	return (1);
}
