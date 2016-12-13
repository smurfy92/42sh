/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:56:16 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 11:38:28 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			key_selection_next(t_group *grp, char *order, int key)
{
	if (key == STAB)
	{
		order[0] = 9;
		order[1] = 0;
		order[2] = 0;
		order[3] = 0;
	}
	if (key == HOME)
		ft_go_home(grp);
	else if (key == END)
		ft_go_end(grp);
	else if (key == ALT_L)
		ft_prev_word(grp);
	else if (key == ALT_R)
		ft_next_word(grp);
	else if (key == ARROW_L || key == ARROW_R ||
		key == ARROW_U || key == ARROW_D)
		handling_arrow(grp, key);
	else if (ft_is_printable(order) || key == STAB)
		print_cmd(grp, order);
	else
		return (0);
	return (1);
}

void		ft_puttab(t_group *grp)
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

int			key_selection(t_group *grp, char *order)
{
	int	key;

	key = KEY(order[0], order[1], order[2], order[3]);
	if (key == TAB)
		comp_init(grp, &grp->comp);
	else if (grp->comp)
		comp_free(grp, &grp->comp);
	if (key == ENTER)
		return (key);
	if (key == CTRL_D)
		handling_ctrl_d(grp);
	else if (key == DEL)
		remove_line(grp);
	else if (key == BACKSPACE || key == DEL)
		handling_backspace(grp);
	else if (key == CTRL_L)
		handling_clear_screen(grp);
	else if (key == PAGE_UP)
		ft_go_up(grp);
	else if (key == PAGE_DOWN)
		ft_go_down(grp);
	else
		return (key_selection_next(grp, order, key));
	return (1);
}

void		read_fd_in(t_group *grp)
{
	char *order;

	TERM(cmd_line) = NEW(0);
	order = NEW(0);
	while (get_next_line(0, &order) > 0)
	{
		TERM(cmd_line) = JOINF(TERM(cmd_line), order, 1);
	}
	REMOVE(&order);
}

static void	get_cmd_help(t_group *grp, int ret_q)
{
	ft_go_end(grp);
	ft_putchar_fd('\n', 2);
	if (TERM(cmd_quote) != NULL)
		fill_cmd_line(grp);
	if (ret_q < 0)
	{
		grp->err_parse = 1;
		error_cmd("parse error", "parenthese closed but not opened", 1);
	}
	check_parentheses(0);
	reset_edl(grp);
}

void		get_cmd(t_group *grp, int fd)
{
	int		ret;
	int		ret_q;
	char	order[BUF_SIZE + 1];

	ret_q = 0;
	if (grp->quit == true)
		return (read_fd_in(grp));
	ft_bzero(order, BUF_SIZE + 1);
	grp->err_parse = 0;
	while ((ret = read(fd, order, BUF_SIZE)) > 0)
	{
		order[ret] = '\0';
		if (key_selection(grp, order) == '\n' && (ret_q = ft_escape(grp)) <= 0)
			break ;
		ft_bzero(order, BUF_SIZE + 1);
	}
	get_cmd_help(grp, ret_q);
}
