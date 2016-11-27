/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:04:13 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/28 00:03:59 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			reset_shell(void)
{
	t_group	*grp;

	grp = get_grp();
	if (tcsetattr(0, 0, &(grp->cpy_term)) == -1)
		return (-1);
	return (0);
}

int			init_shell(void)
{
	char			*name;
	struct termios	term;
	t_group			*grp;
	int				terminal;

	printf("INITSHELL\n");
	terminal = STDIN_FILENO;
	grp = get_grp();
	if ((name = getenv("TERM")) == NULL)
		name = ft_strdup("xterm-256color");
	if (tgetent(NULL, name) == ERR)
		exit(-1);
	if (getenv("TERM") == NULL)
		ft_strdel(&name);
	if (tcgetattr(terminal, &term) == -1)
		return ((grp->quit = true));
	grp->cpy_term = term;
	term.c_lflag = term.c_lflag & (~ICANON & ~ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &term))
	{
		ft_putendl("could not set termcaps's attributes");
		exit(-1);
	}
	return (1);
}
