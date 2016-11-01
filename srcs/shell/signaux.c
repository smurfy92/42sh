/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/10/31 22:46:54 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	handler_win(int sig)
{
	t_group			*grp;
	struct winsize	w;

	grp = get_grp();
	sig = 0;
	ioctl(0, TIOCGWINSZ, &w);
	TERM(window->width) = w.ws_col;
	TERM(window->heigth) = w.ws_row;
}

void	handler_ctrl_c(int sig)
{
	t_group	*grp;

	grp = get_grp();
	sig = 0;
	// if (TERM(cmd_line) == NULL)
	// {
	// 	ft_putchar_fd('\n', 2);
	// 	prompt();
	// 	return ;
	// }
	// else
	// 	ft_putchar_fd('\n', 2);
	ft_go_end(grp);
	REMOVE(&TERM(cmd_line));
	ft_free_parse(grp);
	check_parentheses(0);
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	grp->prompt_size = 6;
	prompt(); 
}

void	ft_prompt(int signum)
{
	char	order[2];
	t_group	*grp;

	signum = 0;
	order[0] = 3;
	order[1] = 0;
	grp = get_grp();
	ioctl(0, TIOCSTI, order);
}

void	sig_handler(void)
{
	signal(SIGTSTP, ft_prompt);
	signal(SIGQUIT, handler_ctrl_c);
	signal(SIGINT, handler_ctrl_c);
	signal(SIGWINCH, handler_win);
}
