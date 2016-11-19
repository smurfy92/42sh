/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:26:46 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/18 17:56:46 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	remplis la liste avec les possibilites et retourne la taille de la liste
*/

t_comp		*new_comp(char *val, t_comp **begin, int type, int start)
{
	t_comp		*new;

	new = (t_comp *)malloc(sizeof(t_comp));
	new->val = ft_strdup(val);
	new->c_type = type;
	new->start = start;
	new->next = (*begin);
	new->prev = (*begin)->prev;
	(*begin)->prev = new;
	new->prev->next = new;
	return (new);
}
