/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:04:13 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/11 04:49:56 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			set_for_jobs(int terminal)
{
	pid_t 		shell_pgid;

	printf("terminal %d shell_pgid stopped: %d\n", tcgetpgrp(terminal), getpgrp ());
	while (tcgetpgrp(terminal) != (shell_pgid = getpgrp ()))
	{
		kill (-shell_pgid, SIGTTIN);
	}
	sig_handler();
	shell_pgid = getpid();
	if (setpgid (shell_pgid, shell_pgid) < 0)
	{
		perror ("Couldn't put the shell in its own process group");
		exit (1);
	}
	tcsetpgrp (terminal, shell_pgid);
	return (0);
}

int			reset_shell(void)
{
	t_group	*grp;
	grp = get_grp();
	if (tcsetattr(0, 0, &(grp->cpy_term)) == -1)
		return (-1);
	return (0);
}

void		restore_shell()
{
	t_group	*grp;

	grp = get_grp();
	tcsetattr (STDIN_FILENO, 0, &grp->curr_term);
}

void		init_shell_job(int pgid, int fg)
{
	int	pid;
	int	is_interact;

	is_interact = isatty (STDIN_FILENO);
	if (is_interact)
	{		
		pid = getpid();
		pgid == 0 ? (pgid = pid) : 0;
		setpgid (pid, pgid);
		fg ? tcsetpgrp (STDIN_FILENO, pgid) : 0;
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGCONT, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
}

int			init_shell(void)
{
	t_group		*grp;
	char		*name;

	grp = get_grp();
	if ((name = getenv("TERM")) == NULL)
		name = ft_strdup("xterm-256color");
	if (tgetent(NULL, name) == ERR)
		exit(-1);
	if (getenv("TERM") == NULL)
		ft_strdel(&name);
	if (tcgetattr(STDIN_FILENO, &grp->curr_term) == -1)
	{
		ft_putendl("could not get termcaps's attributes");
		return ((grp->quit = true));
	}
	grp->cpy_term = grp->curr_term;
	grp->curr_term.c_lflag = grp->curr_term.c_lflag & (~ICANON & ~ECHO);
	grp->curr_term.c_cc[VMIN] = 1;
	grp->curr_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, 0, &grp->curr_term))
	{
		ft_putendl("could not set termcaps's attributes");
		exit(-1);
	}
	return (1);
}
