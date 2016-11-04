/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:41 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/04 13:43:58 by jtranchi         ###   ########.fr       */
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
		printf("  command -> %s$\n",tmp->cmd);
		int i = -1;
		while (CMD(cmdsplit) && CMD(cmdsplit)[++i])
		{
			printf("    cmd->split[%d] %s$\n", i, CMD(cmdsplit[i]));
		}
		printf("  sgred -> %s$\n",tmp->sgred);
		printf("  dbred -> %s$\n",tmp->dbred);
		printf("  file -> %s$\n",tmp->file);
		printf("  heredoc -> %s$\n\n",tmp->heredoc);
		tmp = tmp->next;
	}
}
