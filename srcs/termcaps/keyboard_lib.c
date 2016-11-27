/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:43:58 by julio             #+#    #+#             */
/*   Updated: 2016/11/26 19:07:45 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_go_home(t_group *grp)
{
	while (TERM(curs_pos) > 0)
		ft_left_arrow(grp);
}

void		ft_go_end(t_group *grp)
{
	while (TERM(curs_pos) < TERM(cmd_size))
		ft_right_arrow(grp);
}

void		ft_go_up(t_group *grp)
{
	int i;

	i = -1;
	while (++i < TERM(window->width) && TERM(curs_pos) > 0)
		ft_left_arrow(grp);
}

void		ft_go_down(t_group *grp)
{
	int i;

	i = -1;
	while (++i < TERM(window->width) && TERM(curs_pos) < TERM(cmd_size))
		ft_right_arrow(grp);
}

int			ft_is_printable(char *order)
{
	int	i;

	i = -1;
	while (order[++i] != '\0')
		if (ft_isprint(order[i]) == false)
			return (0);
	return (1);
}
