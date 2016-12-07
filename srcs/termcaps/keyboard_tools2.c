/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:06:09 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/07 22:50:16 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	ft_left_arrow(t_group *grp)
{
	int i;

	if (((((TERM(curs_pos) + START_POS) % TERM(window->width)) == 0) &&
		!ft_contains(grp, TERM(curs_pos))) ||
		TERM(cmd_line)[TERM(curs_pos) - 1] == '\n' ||
		(ft_get_last_eol(grp) % TERM(window->width) == 0 &&
		ft_contains(grp, TERM(curs_pos))))
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
	if (((((TERM(curs_pos) + START_POS) % TERM(window->width)) == 0) &&
		!ft_contains(grp, TERM(curs_pos))) ||
		TERM(cmd_line)[TERM(curs_pos) - 1] == '\n' ||
		(ft_get_last_eol(grp) % TERM(window->width) == 0 &&
		ft_contains(grp, TERM(curs_pos))))
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
