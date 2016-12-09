/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:43:44 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 04:58:29 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	fonctions necessaires a la creation dune var
*/

/*
**	renvoie une struct fraiche pour une nouvelle variable
*/

t_var		*new_var(int type, void *data, char *name)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	new->name = ft_strdup(name);
	new->str = NULL;
	new->nb = NULL;
	new->next = NULL;
	new->type = type;
	if (type == STR_T)
	{
		ft_putendl("CREATING A VARIABLE WITH TYPE STR");
		new->str = ft_strdup((char *)data);
		ft_putendl(new->str);
	}
	else if (type == NUMBER_T)
	{
		ft_putendl("CREATING A VARIABLE WITH TYPE INT");
		new->nb = (int *)data;
		ft_putnbr(*new->nb);
		ft_putendl("");
	}
	return (new);
}

/*
**	checke si une variable existe deja a ce nom
*/

t_var		*check_if_var_exists(char *name, t_script *script)
{
	t_var	*tmp;

	tmp = script->vars;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	modifie un variable existante
*/

static int			update_var(t_var *var, void *value, int type)
{
	if (!value)
		return (E_INSTANT);
	if (type != var->type)
		return (E_CONF_TYPES);
	if (var->type == STR_T)
	{
		ft_strdel(&var->str);
		var->str = ft_strdup((char *)value);
	}
	if (var->type == NUMBER_T)
	{
		free(var->nb);
		var->nb = (int *)value;
	}
	return (0);
}

/*
**	rajoute ou modifie une variable de la liste 
*/

void		add_to_list(t_script *script, t_assign *assign)
{
	t_var	*new;
	t_var	*tmp;
	void	*value;
	int		type;

	tmp = script->vars;
	if (ft_strchr(assign->name, ' '))
	{
		script->errno = E_INSTANT;
		return ;
	}
	if ((new = check_if_var_exists(assign->name, script)))
	{
		if (!(value = assignator(assign, &type)))
		{
			script->errno = E_INSTANT;
			return ;
		}
		if ((script->errno = update_var(new, value, type)))
		{
			return ;
		}
	}
	else
	{
		if (!(value = assignator(assign, &type)))
		{
			script->errno = E_INSTANT;
			return ;
		}
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (tmp)
			tmp->next = new_var(type, value, assign->name);
		else
			script->vars = new_var(type, value, assign->name);
	}
}