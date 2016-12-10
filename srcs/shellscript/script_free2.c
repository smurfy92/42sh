/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_free2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 04:45:12 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/10 08:09:18 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		fold_free(t_fold **to_free)
{
	t_fold		*tmp;

	tmp = *to_free;
	if (tmp)
	{
		if (tmp->dir)
			closedir(tmp->dir);
		ft_strdel(&tmp->tp);
		ft_strdel(&tmp->dirname);
		free(tmp);
	}
	*to_free = NULL;
}

void		loop_free(void **to_free)
{
	t_loop	*tmp;

	tmp = *to_free;
	sc_comp_free(&tmp->comp);
	action_free(&tmp->acts);
	fold_free(&tmp->f_loop);
	free(tmp);
	*to_free = NULL;
}

void		action_free(t_action **begin)
{
	t_action	*tmp;
	t_action	*tp;

	tmp = *begin;
	while (tmp)
	{
		tp = tmp->next;
		if (tmp->type == ASSIGN_T)
			assign_free(&tmp->action);
		else if (tmp->type == LINE_T)
			line_free(&tmp->action);
		else if (tmp->type == COND_T)
			condition_free(&tmp->action);
		else if (tmp->type == LOOP_T)
			loop_free(&tmp->action);
		free(tmp);
		tmp = tp;
	}
}

void		vars_free(t_var **to_free)
{
	t_var	*tmp;
	t_var	*tp;

	tmp = *to_free;
	while (tmp)
	{
		tp = tmp->next;
		if (tmp->str)
			ft_strdel(&tmp->str);
		else
			free(tmp->nb);
		ft_strdel(&tmp->name);
		free(tmp);
		tmp = tp;
	}
	*to_free = NULL;
}

void		free_script(t_script **script)
{
	t_script	*to_free;

	if (*script)
	{
		to_free = *script;
		action_free(&to_free->begin);
		vars_free(&to_free->vars);
		if (to_free->fd)
		{
			close(to_free->fd);
		}
		if (to_free->rd_fd)
		{
			close(to_free->rd_fd);
		}
		free(to_free);
		*script = NULL;
	}
}
