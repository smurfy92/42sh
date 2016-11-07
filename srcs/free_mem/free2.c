/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:51:15 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/07 14:51:16 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_free_andor(t_group *grp)
{
	t_andor *tmp;

	tmp = grp->andor->next;
	REMOVE(&grp->andor->cmd);
	free(grp->andor);
	grp->andor = tmp;
}

void		free_history(t_group *grp)
{
	t_history *hist;
	t_history *tmp;

	hist = ft_history_get_first(grp);
	while (hist)
	{
		REMOVE(&hist->var);
		hist->prev = NULL;
		tmp = hist->next;
		free(hist);
		hist = tmp;
	}
	grp->history = NULL;
}
