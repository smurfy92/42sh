/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 03:04:04 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/08 02:31:09 by jmontija         ###   ########.fr       */
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

	if (sig)
		;
	grp = get_grp();
	if (sig && grp->comp)
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

void	ft_sigchild(int sig, siginfo_t *info, void *context)
{
	t_group	*grp;
	t_jobs	*jobs;

	grp = get_grp();
	if (sig && context)
		;
	jobs = get_jobs_pid(grp, info->si_pid);
	check_jobs_status(jobs);
}

void	sig_handler(void)
{
	struct sigaction sigact;
 
	memset (&sigact, '\0', sizeof(sigact));
	sigact.sa_sigaction = &ft_sigchild;
 	sigact.sa_flags = SA_SIGINFO ;
 	sigaction(SIGCHLD, &sigact, NULL);
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, handler_ctrl_c);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, handler_win);
}
