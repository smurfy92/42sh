/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/16 20:41:50 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void sighandler(int signum, siginfo_t *info, void *ptr)
{
	printf("\nprocess_signal: %lu\n", 
		(unsigned long)getpid());
    printf("Received signal %d\n", signum);
    printf ("Sending PID: %lu, UID: %ld\n",
			(unsigned long)info->si_pid, (long)info->si_uid);
}

void	handler_win(int sig)
{
	t_group			*grp;
	struct winsize	w;

	grp = get_grp();
	if (sig)
	{}
	ioctl(0, TIOCGWINSZ, &w);
	TERM(window->width) = w.ws_col;
	TERM(window->heigth) = w.ws_row;
}

void	handler_ctrl_c(int sig)
{
	t_group	*grp;

	grp = get_grp();
	if (sig)
		{}
	if (grp->comp)
		comp_free(grp, &grp->comp);
	ft_go_end(grp);
	REMOVE(&TERM(cmd_line));
	ft_free_parse(grp);
	check_parentheses(0);
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	grp->prompt_size = 6;
	ft_putchar_fd('\n', 2);
	prompt();

}

void	ft_prompt(int signum)
{
	char	order[2];

	if (signum)
		{}
	order[0] = 3;
	order[1] = 0;
	ioctl(0, TIOCSTI, order);
}

void	sig_handler(void)
{
	struct sigaction act;

	memset (&act, '\0', sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sighandler;

    //sigaction(SIGINT, &act, NULL); // not working yet
    signal(SIGINT, handler_ctrl_c);

	signal(SIGTSTP, ft_prompt);
	signal(SIGQUIT, handler_ctrl_c);
	signal(SIGWINCH, handler_win);

}
