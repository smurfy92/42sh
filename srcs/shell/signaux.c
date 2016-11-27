/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:56:16 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/27 01:07:34 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	handler_win(int sig)
{
	t_group			*grp;
	struct winsize	w;

	grp = get_grp();
	if (sig)
		;
	ioctl(0, TIOCGWINSZ, &w);
	TERM(window->width) = w.ws_col;
	TERM(window->heigth) = w.ws_row;
}

void	handler_ctrl_c(int sig)
{
	t_group	*grp;

	grp = get_grp();
	if (sig && getpid() != grp->program_pid)
		return ;
	if (grp->comp)
		comp_free(grp, &grp->comp);
	ft_go_end(grp);
	ft_free_parse(grp);
	check_parentheses(0);
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	TERM(other_read) = false;
	REMOVE(&TERM(cmd_line));
	grp->prompt_size = 6;
	ioctl(0, TIOCSTI, "\n");
}

void	ft_prompt(int signum)
{
	char	order[2];

	if (signum)
		;
	order[0] = 3;
	order[1] = 0;
	ioctl(0, TIOCSTI, order);
}

void	ft_goeson(int sig)
{
	printf("signal :%d\n", sig);
	t_group	*grp;

	grp = get_grp();
	init_shell();
	ft_exit(grp, 0);
}

void	sig_handler(void)
{
	signal(SIGINT, handler_ctrl_c);
	signal(SIGTSTP, ft_prompt);
	signal(SIGQUIT, handler_ctrl_c);
	signal(SIGWINCH, handler_win);
	signal(SIGTTIN, ft_goeson);
	signal(SIGTTOU, ft_goeson);
	// signal (SIGCHLD, ft_goeson);
}
