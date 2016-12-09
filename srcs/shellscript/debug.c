/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:42:18 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 06:39:32 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	for debug purpose
*/

void			display_action(t_action *begin)
{
	if (begin)
		;
	if (begin)
		;
	t_action		*tmp;
	t_line			*line_tp;
	t_cond			*cond_tp;
	t_assign	*assign_tp;
	t_loop		*loop_tp;

	tmp = begin;
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");
	ft_putendl("DISPLAYING ACTIONS :");
	ft_putendl("");
	while (tmp)
	{
		if (tmp->type == ASSIGN_T)
		{
			assign_tp = (t_assign *)tmp->action;
			ft_putstr("ASSIGNATION : ");
			ft_putstr(assign_tp->name);
			ft_putstr(" = ");
			ft_putendl(assign_tp->value);
			ft_putendl("");
		}
		if (tmp->type == LINE_T)
		{
			line_tp = (t_line *)tmp->action;
			ft_putstr("SIMPLE LINE : ");
			ft_putendl(line_tp->cmd);
		}
		if (tmp->type == LOOP_T)
		{
			loop_tp = (t_loop *)tmp->action;
			ft_putstr("LOOP :");
			ft_putendl(loop_tp->comp->first);
			ft_putchar(loop_tp->comp->type);
			ft_putendl(loop_tp->comp->second);
			display_action(loop_tp->acts);
		}
		if (tmp->type == COND_T)
		{
			cond_tp = (t_cond *)tmp->action;
			while (cond_tp)
			{
				ft_putstr("CONDITION : ");
				if (cond_tp->type == COND_ELSE)
				{
					ft_putendl("allways true, if noooo other");
					display_action(cond_tp->acts);
				}
				else if (cond_tp->type != COND_FI)
				{
					ft_putendl(cond_tp->comp->first);
					ft_putchar(cond_tp->comp->type);
					ft_putendl(cond_tp->comp->second);
					display_action(cond_tp->acts);
				}
				else
					ft_putendl("end of condition");
				cond_tp = cond_tp->next;
			}
		}
		tmp = tmp->next;
	}
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");
}

void			display_vars(t_var *begin)
{
	if (begin)
		;
	t_var		*tmp;

	tmp = begin;
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");
	ft_putendl("VARS :");
	ft_putendl("");
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putstr(" = ");
		if (tmp->type == STR_T)
		{
			ft_putstr(" (str) ");
			ft_putendl(tmp->str);
		}
		else
		{
			ft_putstr(" (int) ");
			ft_putnbr(*tmp->nb);
		}
		ft_putendl((tmp->type == NUMBER_T) ? "\n" : "");
		tmp = tmp->next;
	}
	ft_putendl("");
	ft_putendl("");
	ft_putendl("");
}