/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:41 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/10 23:30:15 by julio            ###   ########.fr       */
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
	t_allcmd *tmp;
	t_andor *tmp2;
	t_parse *tmp3;

	tmp = grp->allcmd;
	while (tmp)
	{
		printf("split ; ->\n");
		tmp2 = tmp->andor;
		while (tmp2)
		{
			tmp3 = tmp2->parselst;
			while (tmp3)
			{
				
				printf("      command -> %s$\n",tmp3->cmd);
				int i = -1;
				while (tmp3->cmdsplit && tmp3->cmdsplit[++i])
					printf("      cmd->split[%d] %s$\n", i, tmp3->cmdsplit[i]);
				printf("      sgred -> %s$\n",tmp3->sgred);
				printf("      dbred -> %s$\n",tmp3->dbred);
				printf("      file -> %s$\n",tmp3->file);
				printf("      close -> %s$\n",tmp3->closefd);
				printf("      redfd -> %s$\n",tmp3->redfd);
				printf("      heredoc -> %s$\n\n",tmp3->heredoc);
				printf("      fd -> %d$\n\n",tmp3->fd);
				if (tmp3->next)
					printf("    pipe ->\n\n");
				tmp3 = tmp3->next;
			}
			if (tmp2->type == 1)
				printf("  andor -> &&\n");
			else if (tmp2->type == 2)
				printf("  andor -> ||\n");
			tmp2 = tmp2->next;
		}
	tmp = tmp->next;
	}
}
