/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:04:13 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 05:06:40 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			set_for_jobs(int terminal)
{
	pid_t 		shell_pgid;

		printf("SET_FOR_JOBS\n");

	/* Loop until we are in the foreground.  */
	while (tcgetpgrp (terminal) != (shell_pgid = getpgrp ()))
	{
		printf("terminal %d shell_pgid stopped: %d\n", terminal, shell_pgid);
		kill (shell_pgid, SIGTTIN);
	}
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

int			reset_shell(void)
{
	t_group	*grp;
	printf("RESET_SHELL\n");
	grp = get_grp();
	if (tcsetattr(0, 0, &(grp->cpy_term)) == -1)
		return (-1);
	return (0);
}

void		restore_shell()
{
	t_group	*grp;

	printf("RESTORE_SHELL\n");
	grp = get_grp();
	//tcsetpgrp (STDIN_FILENO, grp->program_pid);
	//set_for_jobs(STDIN_FILENO);
	tcsetattr (STDIN_FILENO, 0, &grp->curr_term);
}



int			init_shell(void)
{
	t_group		*grp;
	char		*name;

	printf("INITSHELL\n");

	grp = get_grp();
	if ((name = getenv("TERM")) == NULL)
		name = ft_strdup("xterm-256color");
	if (tgetent(NULL, name) == ERR)
		exit(-1);
	if (getenv("TERM") == NULL)
		ft_strdel(&name);
	if (tcgetattr(STDIN_FILENO, &grp->curr_term) == -1)
		return ((grp->quit = true));
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
