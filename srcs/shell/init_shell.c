/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:04:13 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/25 23:38:01 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			reset_shell(void)
{
	t_group	*grp;

	grp = get_grp();
	if (tcsetattr(0, 0, &(grp->cpy_term)) == -1)
		return (-1);
	return (0);
}

int			set_for_jobs(int terminal)
{
	pid_t 		shell_pgid;

	/* Loop until we are in the foreground.  */
	while (tcgetpgrp (terminal) != (shell_pgid = getpgrp ()))
		kill (- shell_pgid, SIGTTIN);
	/* Ignore interactive and job-control signals.  */
	sig_handler();
	/* Put ourselves in our own process group.  */
	shell_pgid = getpid ();
	if (setpgid (shell_pgid, shell_pgid) < 0)
	{
		perror ("Couldn't put the shell in its own process group");
		exit (1);
	}
	/* Grab control of the terminal.  */
	tcsetpgrp (terminal, shell_pgid);
	return (0);
}

int			init_shell(void)
{
	char			*name;
	struct termios	term;
	t_group			*grp;
	int				terminal;
	int				is_interact;

	grp = get_grp();
	terminal = STDIN_FILENO;
	is_interact = isatty(terminal);
	if (is_interact)
	{
		set_for_jobs(terminal);
		if ((name = getenv("TERM")) == NULL)
			name = ft_strdup("xterm-256color");
		if (tgetent(NULL, name) == ERR)
			exit(-1);
		if (getenv("TERM") == NULL)
			ft_strdel(&name);
		if (tcgetattr(terminal, &term) == -1)
			return ((grp->quit = true));
		grp->cpy_term = term;
		term.c_lflag = term.c_lflag & (~ICANON & ~ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if (tcsetattr(0, 0, &term))
		{
			ft_putendl("could not set termcaps's attributes");
			exit(-1);
		}
	}
	else
		grp->quit = true;
	return (1);
}
