/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:41 by jtranchi          #+#    #+#             */
/*   Updated: 2016/10/28 15:10:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_out(char *str)
{
	int fd = open("/dev/ttys001", O_WRONLY|O_NONBLOCK|O_NOCTTY);
	write(fd, str, ft_strlen(str));
}

void		ft_display_parse(t_group *grp)
{
	t_parse *tmp;

	tmp = grp->parselst;
	while (tmp)
	{
		ft_putstr("command -> ");
		ft_putendl(tmp->cmd);
		ft_putstr("sgred -> ");
		ft_putendl(tmp->sgred);
		ft_putstr("dbred -> ");
		ft_putendl(tmp->dbred);
		ft_putstr("file -> ");
		ft_putendl(tmp->file);
		ft_putstr("heredoc -> ");
		ft_putendl(tmp->heredoc);
		tmp = tmp->next;
	}
}
