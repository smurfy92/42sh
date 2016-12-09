/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 03:57:13 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 06:09:46 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		assign_free(void **to_free)
{
	t_assign	*tmp;

	tmp = *to_free;
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->value);
	free(tmp);
	*to_free = NULL;
}

void		line_free(void **to_free)
{
	t_line	*tmp;

	tmp = *to_free;
	ft_strdel(&tmp->cmd);
	free(*to_free);
	*to_free = NULL;
}

void		sc_comp_free(t_com **to_free)
{
	t_com	*tmp;

	tmp = *to_free;
	if (tmp)
	{
		ft_strdel(&tmp->first);
		ft_strdel(&tmp->second);
		free(tmp);
	}
	*to_free = NULL;
}

void		condition_free(void **to_free)
{
	t_cond	*tmp;
	t_cond	*tp;

	tmp = *to_free;
	while (tmp)
	{
		tp = tmp->next;
		ft_strdel(&tmp->text);
		action_free(&tmp->acts);
		sc_comp_free(&tmp->comp);
		free(tmp);
		tmp = tp;
	}
	*to_free = NULL;
}
