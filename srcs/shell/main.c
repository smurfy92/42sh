/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/10 23:16:45 by julio            ###   ########.fr       */
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
void		ft_init_parse(t_group *grp)
{
	t_allcmd *tabl;
	t_andor *tmp2;

	tabl = grp->allcmd;
	while (tabl)
	{
		tabl->andor = ft_strsplitandor(tabl->cmd);
		tmp2 = tabl->andor;
		while (tmp2)
		{
			ft_parse(grp, tmp2);
			tmp2 = tmp2->next;
		}
		tabl = tabl->next;
	}
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
	ft_display_parse(grp);
	init_exec(grp);
	ft_free_parse(grp);
	free(grp->allcmd);
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
	hash_init(&grp->root, grp);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
