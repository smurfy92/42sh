/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 23:45:59 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/21 00:41:38 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		update_path_env(t_group *grp, t_envlst *new)
{
	if (ft_strcmp(new->name, "PATH") == 0)
	{
		root_hfree(&grp->root);
		hash_init(&grp->root, grp, NULL);
	}
}

int				unset_env(t_group *grp, char *todel)
{
	t_envlst *curr;
	t_envlst *prev;

	prev = NULL;
	curr = grp->env->lst;
	ft_strcmp(todel, "_") == 0 ? todel = NULL : 0;
	ft_strcmp(todel, "SHLVL") == 0 ? todel = NULL : 0;
	while (todel != NULL && curr != NULL)
	{
		if ((ft_strcmp(curr->name, todel) == 0))
		{
			if (prev == NULL)
				grp->env->lst = curr->next;
			else
				prev->next = curr->next;
			ft_strcmp(todel, "PATH") == 0 ? root_hfree(&grp->root) : 0;
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

	curr_env = grp->env->lst;
	if ((i = is_env(env)) == false)
		return (NULL);
	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!(new) || !(env))
		return (NULL);
	new->exist = false;
	new->name = SUB(env, 0, i);
	new->val = SUB(env, i + 1, LEN(env));
	while (curr_env != NULL)
	{
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


static int		free_and_return(t_envlst *new, t_group *grp)
{
	if (ft_strcmp(new->name, "PATH") == 0)
	{
		root_hfree(&grp->root);
		hash_init(&grp->root, grp, NULL);
	}
	REMOVE(&new->val);
	REMOVE(&new->name);
	free(new);
	new = NULL;
	return (1);
}

int				insert_env(t_group *grp, char *env)
{
	t_envlst	*new;
	t_envlst	*tmp;
	char		*tmp2;
	int			i;

	i = 0;
	tmp = grp->env->lst;
	tmp2 = ft_strtrim(env);
	new = create_env_line(grp, tmp2, i);
	REMOVE(&tmp2);
	if (new == NULL)
		return (-1);
	if (new->exist == true)
		return (free_and_return(new, grp));
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		grp->env->lst = new;
	update_path_env(grp, new);
	return (1);
}
