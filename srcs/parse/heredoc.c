/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:52:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/13 04:41:22 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		heredoc(t_group *grp, char *file, char *eof)
{
	int		fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0755);
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	REMOVE(&TERM(cmd_line));
	while (42)
	{
		ft_putstr("$>");
		grp->prompt_size = 2;
		get_cmd(grp, 0);
		if (TERM(cmd_line) && ft_strcmp(TERM(cmd_line), eof) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		REMOVE(&TERM(cmd_line));
	}
}

void		check_heredoc(t_group *grp)
{
	char	**hdoc;
	char	*file;
	int		i;

	t_allcmd *tmp;
	t_andor *tmp2;
	t_parse *tmp3;

	hdoc = NULL;
	tmp = grp->allcmd;
	while (tmp)
	{
		tmp2 = tmp->andor;
		while (tmp2)
		{
			tmp3 = tmp2->parselst;
			while (tmp3)
			{
				if (tmp3->heredoc != NULL)
				{
					i = -1;
					grp->hdcount += 1;
					file = JOINF("hdoc_", ft_itoa(grp->hdcount), 2);
					hdoc = ft_strsplit(tmp3->heredoc, ';');
					while (hdoc[++i])
						heredoc(grp, file, hdoc[i]);
					if (tmp3->file == NULL)
						tmp3->file = SDUP(file);
					REMOVE(&file);
					ft_freestrtab(&hdoc);
				}
				tmp3 = tmp3->next;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

// think to remove file on ctrl+d, ctrl+c and all possibilty to quit the hdoc prematurly
// afficher erreur parse after heredoc 