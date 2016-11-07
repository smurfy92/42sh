/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/06 18:34:12 by jmontija         ###   ########.fr       */
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

void		ft_free_andor(t_group *grp)
{
	t_andor *tmp;

	tmp = grp->andor->next;
	REMOVE(&grp->andor->cmd);
	free(grp->andor);
	grp->andor = tmp;
}

void		proccess(t_group *grp)
{
	int		i;
	char	**tabl;

	i = -1;
	prompt();
	get_cmd(grp, 0);
	ft_pre_parse(grp);
	if (LEN(TERM(cmd_line)) > 0)
		ft_add_history(grp, TERM(cmd_line));
	tabl = ft_strsplitquote(TERM(cmd_line), ';');
	while (tabl && tabl[++i])
	{
		grp->andor = ft_strsplitandor(tabl[i]);
		REMOVE(&tabl[i]);
		while (grp->andor)
		{
			printf("andor->: %s -> %d\n", grp->andor->cmd, grp->andor->type);
			ft_parse(grp, grp->andor->cmd);

			ft_display_parse(grp);
			init_exec(grp);
			ft_free_parse(grp);
			ft_free_andor(grp);
		}
	}
	free(tabl);
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
