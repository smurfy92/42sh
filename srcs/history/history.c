/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:49:38 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 14:25:26 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_add_history(t_group *grp, char *cmd)
{
	int			fd;
	t_history	*tmp;

	fd = open("/tmp/.42sh_history", O_WRONLY | O_APPEND | O_CREAT,
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	ft_putendl_fd(cmd, fd);
	tmp = (t_history*)malloc(sizeof(t_history));
	tmp->var = ft_strdup(cmd);
	tmp->next = NULL;
	tmp->prev = NULL;
	close(fd);
	if (!grp->history)
	{
		tmp->i = 1;
		grp->history = tmp;
		return ;
	}
	while (grp->history->next)
		grp->history = grp->history->next;
	grp->history->next = tmp;
	tmp->i = grp->history->i + 1;
	tmp->prev = grp->history;
	grp->history = grp->history->next;
	grp->inhistory = 0;
}

void		ft_history_prev(t_group *grp)
{
	if (!grp->history || (!grp->history && !grp->history->prev &&
	grp->inhistory))
		return ;
	if (!grp->history->next && TERM(cmd_line) && LEN(TERM(cmd_line)) > 0
		&& !grp->inhistory)
	{
		ft_add_history(grp, TERM(cmd_line));
		(grp->history->prev) ? (grp->history = grp->history->prev) : 0;
	}
	remove_line(grp);
	grp->inhistory = 1;
	if (grp->history->prev && grp->inhistory)
		grp->history = grp->history->prev;
	if (grp->history->var)
	{
		TERM(curs_pos) = ft_strlen(grp->history->var);
		TERM(cmd_size) = ft_strlen(grp->history->var);
		REMOVE(&TERM(cmd_line));
		TERM(cmd_line) = ft_strdup(grp->history->var);
		ft_putstr_fd(TERM(cmd_line), 2);
	}
}

void		ft_history_next(t_group *grp)
{
	if (!grp->history)
		return ;
	if (TERM(cmd_line))
		remove_line(grp);
	if (grp->history->next)
	{
		grp->history = grp->history->next;
		TERM(curs_pos) = ft_strlen(grp->history->var);
		TERM(cmd_size) = ft_strlen(grp->history->var);
		TERM(cmd_line) = ft_strdup(grp->history->var);
		ft_putstr_fd(TERM(cmd_line), 2);
	}
	else
		grp->inhistory = 0;
}

void		ft_get_history(t_group *grp)
{
	int			fd;
	t_history	*tmp;
	char		*line;

	grp->history = NULL;
	fd = open("/tmp/.42sh_history", O_RDONLY | O_CREAT,
	S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	while ((get_next_line(fd, &line)) > 0)
	{
		tmp = (t_history*)malloc(sizeof(t_history));
		tmp->var = ft_strdup(line);
		tmp->next = NULL;
		tmp->prev = NULL;
		if (!grp->history && (tmp->i = 1))
			grp->history = tmp;
		else
		{
			grp->history->next = tmp;
			tmp->i = grp->history->i + 1;
			tmp->prev = grp->history;
			grp->history = grp->history->next;
		}
		ft_strdel(&line);
	}
	close(fd);
}
