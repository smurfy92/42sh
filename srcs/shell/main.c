/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 20:11:03 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_getchar(int c)
{
	return (write(2, &c, 1));
}

void		prompt(void)
{
	t_group *grp;

	grp = get_grp();
	if (grp->quit == false)
		ft_putstr_fd("42sh> ", 2);
}

void		proccess(t_group *grp)
{
	prompt();
	get_cmd(grp, 0);
	TERM(other_read) = false;
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	if (grp->err_parse == false)
	{
		grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
		ft_init_parse(grp);
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
		{}
	init_shell();
	grp = get_grp();
	grp->program_name = SDUP(argv[0]);
	grp->program_pid = getpid();
	init_env(grp, env);
	hash_init(&grp->root, grp, NULL);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
