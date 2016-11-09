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
	t_allcmd *tabl;
	t_andor *tmp2;

	prompt();
	get_cmd(grp, 0);
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
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
	ft_display_parse(grp);
	t_parse *tmp3;
	while (grp->allcmd)
	{
		tabl = grp->allcmd;
		REMOVE(&tabl->cmd);
		while (tabl->andor)
		{
			tmp2 = tabl->andor;
			REMOVE(&tabl->andor->cmd);
			while (tmp2->parselst)
			{
				tmp3 = tmp2->parselst;
				init_exec(grp);
				tmp2->parselst = tmp3->next;
				free_parselst(tmp3);
			}
			tabl->andor = tmp2->next;
			free(tmp2);
		}
		grp->allcmd = tabl->next;
		free(tabl);
		tabl = grp->allcmd;
	}
	ft_free_parse(grp);
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
