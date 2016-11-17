/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 19:31:01 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 18:00:42 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	ft_replace_cursor(t_group *grp)
{
	int i;
	int y;

	i = -1;
	while (++i < (int)ft_strlen(&TERM(cmd_line)[TERM(curs_pos)]))
	{
		if (((TERM(curs_pos) + START_POS +
			(int)ft_strlen(&TERM(cmd_line)[TERM(curs_pos)]) - i) %
			TERM(window->width)) == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_getchar);
			y = 0;
			while (y++ < TERM(window->width))
				tputs(tgetstr("nd", NULL), 0, ft_getchar);
		}
		else
			tputs(tgetstr("le", NULL), 0, ft_getchar);
	}
}

void	ft_get_cmd(t_group *grp, char *order)
{
	char	*tmp;

	if (TERM(curs_pos) < TERM(cmd_size))
	{
		tmp = JOIN(order, (TERM(cmd_line) + TERM(curs_pos)));
		TERM(cmd_line)[TERM(curs_pos)] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 3);
	}
	else
	{
		if (!TERM(cmd_line))
			TERM(cmd_line) = ft_strdup(order);
		else
			TERM(cmd_line) = JOINF(TERM(cmd_line), order, 1);
	}
	TERM(curs_pos) += LEN(order);
	TERM(cmd_size) = LEN(TERM(cmd_line));
	ft_putstr_fd(order, 2);
}

void	print_cmd(t_group *grp, char *order)
{
	int i;

	i = -1;
	ft_get_cmd(grp, order);
	if (TERM(curs_pos) < TERM(cmd_size))
	{
		i = TERM(curs_pos) - 1;
		while (TERM(cmd_line)[++i])
			ft_putchar_fd(TERM(cmd_line)[i], 2);
		if (((i + START_POS) % TERM(window->width)) == 0)
			tputs(tgetstr("do", NULL), 0, ft_getchar);
		ft_replace_cursor(grp);
	}
	else if ((START_POS + TERM(curs_pos)) % TERM(window->width) == 0)
		tputs(tgetstr("do", NULL), 0, ft_getchar);
	// grp->is_search == true ? find_search(grp) : 0;
}

void	handling_ctrl_d(t_group *grp)
{
	char	*tmp;
	
	if (TERM(cmd_size) == 0)
		ft_strdel(&TERM(cmd_line));
	if (TERM(cmd_size) == 0 && TERM(other_read) == false)
	{
		reset_shell();
		ft_putstr_fd("\n", 2);
		ft_exit(grp, 0);
	}
	else if (TERM(curs_pos) < TERM(cmd_size))
	{
		tmp = &TERM(cmd_line)[TERM(curs_pos) + 1];
		TERM(cmd_line)[TERM(curs_pos)] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 1);
		TERM(cmd_size) -= 1;
		tputs(tgetstr("dc", NULL), 0, ft_getchar);
		tputs(tgetstr("cd", NULL), 0, ft_getchar);
		tputs(tgetstr("sc", NULL), 0, ft_getchar);
		ft_putstr_fd(&TERM(cmd_line)[TERM(curs_pos)], 2);
		tputs(tgetstr("rc", NULL), 0, ft_getchar);
	}
}

void	handling_backspace(t_group *grp)
{
	char *tmp;

	if (TERM(curs_pos) == 0)
		return ;
	tmp = &TERM(cmd_line)[TERM(curs_pos)];
	ft_left_arrow(grp);
	TERM(cmd_size)--;
	if (TERM(cmd_size) == 0)
		ft_strdel(&TERM(cmd_line));
	else
	{
		TERM(cmd_line)[TERM(curs_pos)] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 1);
	}
	tputs(tgetstr("dc", NULL), 0, ft_getchar);
	tputs(tgetstr("cd", NULL), 0, ft_getchar);
	tputs(tgetstr("sc", NULL), 0, ft_getchar);
	ft_putstr_fd(&TERM(cmd_line)[TERM(curs_pos)], 2);
	tputs(tgetstr("rc", NULL), 0, ft_getchar);
	// grp->is_search == true ? find_search(grp) : 0;
}
