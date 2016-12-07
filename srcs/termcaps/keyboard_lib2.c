/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_lib2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 22:56:18 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/07 22:52:01 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_contains(t_group *grp, int i)
{
	while (--i > 0)
	{
		if (TERM(cmd_line)[i] == '\n')
			return (1);
	}
	return (0);
}

int		ft_get_last_eol(t_group *grp)
{
	int i;
	int y;

	i = TERM(curs_pos);
	y = 0;
	while (--i >= 0 && TERM(cmd_line)[i] && TERM(cmd_line)[i] != '\n')
		y++;
	return (y);
}

void	ft_place_to_eof(t_group *grp)
{
	int i;

	(void)grp;
	i = TERM(window->width) % TERM(window->width);
	if (ft_contains(grp, TERM(curs_pos)))
		i = ft_get_last_eol(grp);
	while (--i > 0)
		tputs(tgetstr("le", NULL), 0, ft_getchar);
	i = 2;
	while (TERM(cmd_line)[TERM(curs_pos) - i - 1] != '\n' &&
		TERM(curs_pos) + START_POS - i != 0)
		i++;
	i = i % TERM(window->width);
	if (!ft_contains(grp, TERM(curs_pos)))
		i += START_POS;
	while (--i > 0)
		tputs(tgetstr("nd", NULL), 0, ft_getchar);
}

void	ft_puttab(t_group *grp)
{
	char *tmp;
	char *ch;

	ch = ft_strnew(1);
	ch[0] = '\t';
	tmp = SDUP(&TERM(cmd_line)[TERM(curs_pos)]);
	TERM(cmd_line)[TERM(curs_pos)] = '\0';
	TERM(cmd_line) = JOINF(TERM(cmd_line), ch, 3);
	TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 3);
}
