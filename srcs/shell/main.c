/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 17:07:07 by julio            ###   ########.fr       */
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
		ft_parse(grp, tabl[i]);
		//check command -> add flag error
		//ft_display_parse(grp);
		init_exec(grp); //exec
		ft_free_parse(grp);
		ft_strdel(&tabl[i]);
	}
	free(tabl);
	ft_strdel(&TERM(cmd_line));
}

int			main(int argc, char **argv, char **env)
{
	t_group *grp;

	if (argc || argv){}
	init_shell();
	grp = get_grp();
	init_env(grp, env);
	sig_handler();
	while (42)
		proccess(grp);
	reset_shell();
	return (0);
}
