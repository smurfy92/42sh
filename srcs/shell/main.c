/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:26:28 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/13 21:29:32 by jmontija         ###   ########.fr       */
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
	if (LEN(TERM(cmd_line)) > 0 && grp->is_interact != false)
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
	REMOVE(&TERM(cmd_line));
}

int			main(int argc, char **argv, char **env)
{
	t_group *grp;

	grp = get_grp();
	grp->program_name = SDUP(argv[0]);
	grp->program_pid = getpid();
	grp->is_interact = isatty(STDIN_FILENO);
	if (grp->is_interact)
	{
		set_for_jobs(STDIN_FILENO);
		init_shell();
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	init_env(grp, env);
	(argc >= 2) ? init_shellscript(argc, argv, grp) : 0;
	while (42)
		proccess(grp);
	return (0);
}
