/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 05:39:25 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_getchar(int c)
{
	return (write(2, &c, 1));
}

void		prompt(void)
{
	char	order[512];

	ft_bzero(order, 513);
	fcntl(0, F_GETPATH, order);
	if (ft_strstr(order, "/dev/ttys") != NULL) // leaks
		ft_putstr_fd("42sh> ", 2);
	ft_bzero(order, 513);
}

void		proccess(t_group *grp)
{
	prompt();
	get_cmd(grp, 0);
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
	ft_init_parse(grp);
	//ft_display_parse(grp);
	init_exec(grp);
	ft_free_parse(grp);
	free(grp->allcmd);
	ft_strdel(&TERM(cmd_line));
	if (grp->quit)
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
	init_env(grp, env);
	hash_init(&grp->root, grp, NULL);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
