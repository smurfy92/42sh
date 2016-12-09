/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:19:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 04:57:34 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	rajoute une nouvelle action a la fin de la liste d'action
*/

void			add_to_action(void *action, t_script *script,
	int type, t_action **begin)
{
	t_action		*new;
	t_action		*tmp;

	if (script)
		;
	if (!action)
		error_handler(script);
	new = (t_action *)malloc(sizeof(t_action));
	new->type = type;
	new->action = action;
	new->next = NULL;
	tmp = *begin;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*begin = new;
	else
		tmp->next = new;
}
