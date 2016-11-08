/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/08 17:22:33 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_getchar(int c)
{
	return (write(2, &c, 1));
}

int			reset_shell(void)
{
	t_group			*grp;

	grp = get_grp();
	if (tcsetattr(0, 0, &grp->cpy_term) == -1)
		return (-1);
	return (0);
}

void		prompt(void)
{
	ft_putstr_fd("42sh> ", 2);
}

void		proccess(t_group *grp)
{
	t_andor *tabl;

	prompt();
	get_cmd(grp, 0);
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
	tabl = grp->allcmd;
	while (tabl)
	{
		grp->andor = ft_strsplitandor(tabl->cmd);
		REMOVE(&tabl->cmd);
		while (grp->andor)
		{
			printf("andor->: %s -> %d\n", grp->andor->cmd, grp->andor->type);
			ft_parse(grp, grp->andor->cmd);
			ft_display_parse(grp);
			init_exec(grp);
			ft_free_parse(grp);
			ft_free_andor(grp);
		}
		tabl = tabl->next;
	}
	free(tabl); // free les maillon avant
	ft_strdel(&TERM(cmd_line));
	grp->hdcount = 0;
}

int			main(int argc, char **argv, char **env)
{
	t_group *grp;

	if (argc || argv)
		{}
	init_shell();
	grp = get_grp();
	init_env(grp, env);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
