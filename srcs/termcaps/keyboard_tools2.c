/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:06:09 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 19:15:47 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** void	display_historic(t_group *grp)
** {
** 	ft_putstr_fd(grp->curr_hist->name, 2);
** 	if ((START_POS + LEN(grp->curr_hist->name)) % TERM(window->width) == 0)
** 		tputs(tgetstr("do", NULL), 0, ft_getchar);
** 	TERM(cmd_line) = SDUP(grp->curr_hist->name);
** 	TERM(curs_pos) += LEN(TERM(cmd_line));
** 	TERM(cmd_size) = TERM(curs_pos);
** }
** void	handling_historic(t_group *grp, int key)
** {
** 	grp->is_search ? canceled_search(grp) : 0;
** 	remove_line(grp);
** 	if (key == ARROW_U && grp->hist)
** 	{
** 		if (grp->curr_hist == NULL)
** 			grp->curr_hist = grp->hist;
** 		else if (grp->curr_hist->next)
** 			grp->curr_hist = grp->curr_hist->next;
** 		display_historic(grp);
** 	}
** 	else if (key == ARROW_D && grp->hist)
** 	{
** 		if (grp->curr_hist != NULL)
** 			grp->curr_hist = grp->curr_hist->prev;
** 		if (grp->curr_hist != NULL)
** 			display_historic(grp);
** 		else
** 			remove_line(grp);
** 	}
** }
*/

void	ft_place_to_eof(t_group *grp)
{
	int i;

	(void)grp;
	i = TERM(window->width);
	while (--i > 0)
		tputs(tgetstr("le", NULL), 0, ft_getchar);
	i = 2;
	while (TERM(cmd_line)[TERM(curs_pos) - i - 1] != '\n' &&
		TERM(curs_pos) + START_POS - i != 0)
		i++;
	while (--i > 0)
		tputs(tgetstr("nd", NULL), 0, ft_getchar);
}

void	ft_left_arrow(t_group *grp)
{
	int i;

	if ((((TERM(curs_pos) + START_POS) % TERM(window->width)) == 0) ||
		TERM(cmd_line)[TERM(curs_pos) - 1] == '\n')
	{
		i = 0;
		tputs(tgetstr("up", NULL), 0, ft_getchar);
		if (TERM(cmd_line)[TERM(curs_pos) - 1] == '\n')
			ft_place_to_eof(grp);
		else
			while (++i < TERM(window->width))
				tputs(tgetstr("nd", NULL), 0, ft_getchar);
	}
	else
		tputs(tgetstr("le", NULL), 0, ft_getchar);
	TERM(curs_pos) -= 1;
}

void	ft_right_arrow(t_group *grp)
{
	TERM(curs_pos) += 1;
	if (((TERM(curs_pos) + START_POS) % TERM(window->width)) == 0 ||
		TERM(cmd_line)[TERM(curs_pos) - 1] == '\n')
		tputs(tgetstr("do", NULL), 0, ft_getchar);
	else
		tputs(tgetstr("nd", NULL), 0, ft_getchar);
}

void	handling_arrow(t_group *grp, int key)
{
	if (key == ARROW_U)
		ft_history_prev(grp);
	else if (key == ARROW_D)
		ft_history_next(grp);
	if (key == ARROW_L && TERM(curs_pos) > 0)
		ft_left_arrow(grp);
	else if (key == ARROW_R && TERM(curs_pos) < (int)LEN(TERM(cmd_line)))
		ft_right_arrow(grp);
}
