/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 15:10:31 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 14:20:02 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

t_history		*ft_history_get_last(t_group *grp)
{
	t_history	*tmp;

	tmp = grp->history;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_history		*ft_history_get_first(t_group *grp)
{
	t_history	*tmp;

	tmp = grp->history;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

t_history		*ft_history_get_by_id(t_group *grp, int nb)
{
	t_history	*tmp;

	tmp = ft_history_get_first(grp);
	while (tmp)
	{
		if (tmp->i == nb)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
