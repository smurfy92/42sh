/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:52:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/06 18:34:37 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		heredoc(t_group *grp, int count, char *eof)
{
	int		fd;
	char	*file;

	file = JOIN("hdoc_", ft_itoa(count));
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	TERM(curs_pos) = 0;
	TERM(cmd_size) = 0;
	REMOVE(&TERM(cmd_line));
	REMOVE(&file);
	while (42)
	{
		ft_putstr("$>");
		grp->prompt_size = 2;
		get_cmd(grp, 0);
		if (ft_strcmp(TERM(cmd_line), eof) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		REMOVE(&TERM(cmd_line));
	}
}

void		check_heredoc(t_group *grp)
{
	t_parse *tmp;
	char	**hdoc;
	int		i;

	hdoc = NULL;
	tmp = grp->parselst;
	while (tmp)
	{
		if (tmp->heredoc != NULL)
		{
			i = -1;
			grp->hdcount += 1;
			hdoc = ft_strsplit(tmp->heredoc, ';');
			while (hdoc[++i])
				heredoc(grp, grp->hdcount, hdoc[i]);
			ft_freestrtab(&hdoc);
		}
		tmp = tmp->next;
	}
}