/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:56:16 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/21 23:51:20 by jmontija         ###   ########.fr       */
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
		ft_free_parse(grp);
		free(grp->allcmd);
	}
	ft_strdel(&TERM(cmd_line));
	if (grp->quit == true)
		ft_exit(grp, grp->exit);
	grp->hdcount = 0;
}

int			main(int argc, char **argv, char **env)
{
	t_group *grp;

	if (argc || argv)
		;
	init_shell();
	grp = get_grp();
	grp->program_name = SDUP(argv[0]);
	grp->program_pid = getpid();
	init_env(grp, env);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
