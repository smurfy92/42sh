/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 03:04:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 21:22:44 by jmontija         ###   ########.fr       */
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
	printf("ctrl_c\n");
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

void	handler_ctrl_z(int signum)
{
	char	order[2];

	if (signum)
		;
	order[0] = 3;
	order[1] = 0;
	ioctl(0, TIOCSTI, order);
}

void	handler_ttinout(int sig)
{
	t_group	*grp;

	grp = get_grp();
	printf("curr_pid: %d\nsignal: %d\n", getpid(), sig);
	tcsetpgrp (STDIN_FILENO, grp->program_pid);
	restore_shell();
	//reset_shell();
	//set_for_jobs(STDIN_FILENO);
	//init_shell();
}

void	sig_handler(void)
{
	printf("SIGNAUX\n");
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, handler_ctrl_c);
	signal(SIGTSTP, handler_ctrl_z);
	signal(SIGTTIN, handler_ttinout);
	signal(SIGTTOU, handler_ttinout);
	signal(SIGWINCH, handler_win);
}
