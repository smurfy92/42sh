/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:06:09 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/20 00:12:36 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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
