/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:56:16 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/28 00:03:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_getchar(int c)
{
	return (write(2, &c, 1));
}

void		proccess(t_group *grp)
{
	prompt();
	get_cmd(grp, 0);
	TERM(other_read) = false;
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	if (grp->err_parse == false && TERM(cmd_line))
	{
		grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
		ft_init_parse(grp);
		if (grp->err_parse == false)
			init_exec(grp);
		remove_hdoc(grp);
		ft_free_parse(grp);
		free(grp->allcmd);
	}
	ft_strdel(&TERM(cmd_line));
	if (grp->quit == true)
		ft_exit(grp, grp->exit);
	grp->hdcount = 0;
}

int			set_for_jobs(int terminal)
{
	pid_t 		shell_pgid;

		printf("SET_FOR_JOBS\n");

	/* Loop until we are in the foreground.  */
	while (tcgetpgrp (terminal) != (shell_pgid = getpgrp ()))
	{
		printf("terminal %d shell_pgid: %d\n", terminal, shell_pgid);
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

int			main(int argc, char **argv, char **env)
{
	// int		is_interact;
	// int terminal;
	t_group *grp;

	if (argc || argv)
		;
	grp = get_grp();
	grp->program_name = SDUP(argv[0]);
	grp->program_pid = getpid();
	grp->is_interact = isatty(STDIN_FILENO);
	if (grp->is_interact)
	{
		set_for_jobs(STDIN_FILENO);
		init_shell();
	}
	init_env(grp, env);
	//insert_env(grp, JOINF("42PID=", ft_atoi(getpid()), 2));
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
