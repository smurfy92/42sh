/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:51:15 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/21 22:18:53 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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

void		free_allandor(t_andor **andor)
{
	t_andor	*tmp;
	t_andor	*tmp2;

	tmp = *andor;
	while (tmp)
	{
		tmp2 = tmp->next;
		REMOVE(&tmp->cmd);
		free_allparse(tmp);
		free(tmp);
		tmp = tmp2;
	}
	*andor = NULL;
}

void		free_allcmd(t_group *grp)
{
	t_allcmd	*tmp;
	t_allcmd	*tmp2;

	tmp = grp->allcmd;
	while (tmp)
	{
		tmp2 = tmp->next;
		REMOVE(&tmp->cmd);
		free_allandor(&tmp->andor);
		free(tmp);
		tmp = tmp2;
	}
	grp->allcmd = NULL;
}

void		ft_free_parse(t_group *grp)
{
	char	*file;

	free_term(grp);
	free_env_tmp(grp);
	check_parentheses(0);
	free_allcmd(grp);
	while (grp->hdcount > 0)
	{
		file = JOINF("hdoc_", ft_itoa(grp->hdcount), 2);
		unlink(file);
		REMOVE(&file);
		grp->hdcount -= 1;
	}
}
