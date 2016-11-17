/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 17:05:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 20:19:52 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_is_printable(char *order)
{
	int	i;

	i = -1;
	while (order[++i] != '\0')
		if (ft_isprint(order[i]) == false)
			return (0);
	return (1);
}

int		key_selection_next(t_group *grp, char *order, int key)
{
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
	else if (ft_is_printable(order))
		print_cmd(grp, order);
	else
		return (0);
	return (1);
}

int		key_selection(t_group *grp, char *order)
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

void read_fd_in(t_group *grp)
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

void	get_cmd(t_group *grp, int fd)
{
	int		ret;
	int		ret_quote;
	char	order[BUF_SIZE + 1];

	ret_quote = 0;
	if (grp->quit == true)
	{
		read_fd_in(grp);
		return ;
	}
	ft_bzero(order, BUF_SIZE + 1);
	grp->err_parse = 0;
	while ((ret = read(fd, order, BUF_SIZE)) > 0)
	{
		order[ret] = '\0';
		if (key_selection(grp, order) == '\n' && (ret_quote = ft_escape(grp)) == 0)
			break ;
		if (ret_quote < 0)
			break ;
		ft_bzero(order, BUF_SIZE + 1);
	}
	ft_go_end(grp);
	ft_putchar_fd('\n', 2);
	if (TERM(cmd_quote) != NULL)
		fill_cmd_line(grp);
	if (ret_quote < 0)
	{
		grp->err_parse = 1;
		error_cmd("42sh: parse error", "parenthese closed too soon", 1);
	}
	ft_bzero(order, BUF_SIZE + 1);
	check_parentheses(0);
	reset_edl(grp);
}
