/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:17:06 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/09 16:04:25 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"


int			init_shell(void)
{
	char			*name;
	struct termios	term;
	t_group			*grp;

	grp = get_grp();
	if ((name = getenv("TERM")) == NULL)
		name = ft_strdup("xterm-256color");
	if (tgetent(NULL, name) == ERR)
		exit(-1);
	if (getenv("TERM") == NULL)
		ft_strdel(&name);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	grp->cpy_term = term;
	term.c_lflag = term.c_lflag & (~ICANON & ~ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &term))
		exit(-1);
	return (1);
}

void		init_term(t_group *grp)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	grp->term = (t_term *)malloc(sizeof(t_term));
	grp->term->curs_pos = 0;
	grp->term->line = 0;
	grp->term->cmd_size = 0;
	grp->term->other_read = 0;
	grp->term->cmd_line = NULL;
	grp->term->cmd_quote = NULL;
	grp->term->search = NULL;
	grp->term->window = (t_window *)malloc(sizeof(t_window));
	grp->term->window->width = w.ws_col;
	grp->term->window->heigth = w.ws_row;
}

t_group		*set_grp(t_group *grp)
{
	grp = (t_group*)ft_memalloc(sizeof(t_group));
	grp->env = (t_env *)malloc(sizeof(t_env));
	grp->env->lst = NULL;
	grp->env->lst_tmp = NULL;
	grp->env->opt_i = false;
	grp->env->start_varenv = 0;
	grp->env->end_varenv = 0;
	grp->env->cmd = NULL;
	grp->prompt_size = 6;
	grp->exit = 0;
	grp->hdcount = 0;
	grp->andor = NULL;
	ft_get_history(grp);
	init_term(grp);
	grp->root = NULL;
	hash_init(&grp->root, grp);
	return (grp);
}

t_group		*get_grp(void)
{
	static t_group *grp = NULL;

	if (!grp)
		grp = set_grp(grp);
	return (grp);
}
