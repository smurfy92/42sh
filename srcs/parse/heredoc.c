/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:52:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 23:39:05 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** printing prompt for heredoc if has one or more
*/

int			check_and_return(t_group *grp)
{
	if (TERM(other_read) == false)
	{
		grp->err_parse = true;
		return (-1);
	}
	TERM(other_read) = false;
	return (0);
}

int			heredoc(t_group *grp, char *file, char *eof)
{
	int		fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0755);
	free_term(grp);
	REMOVE(&TERM(cmd_line));
	check_parentheses(0);
	TERM(other_read) = true;
	while (42)
	{
		grp->prompt_size = 7;
		ft_putstr("hdocs> ");
		get_cmd(grp, 0);
		if (TERM(other_read) == false)
			break ;
		if (TERM(cmd_line) && ft_strcmp(TERM(cmd_line), eof) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		free_term(grp);
		REMOVE(&TERM(cmd_line));
	}
	close(fd);
	return (check_and_return(grp));
}

/*
** checking if command has heredocs and activates heredoc prompt
*/

int			prepare_heredoc(t_group *grp, t_parse *tmp3)
{
	char	**hdoc;
	char	*file;
	int		ret;
	int		i;

	hdoc = NULL;
	ret = 0;
	if (tmp3->heredoc != NULL)
	{
		i = -1;
		grp->hdcount += 1;
		file = JOINF("hdoc_", ft_itoa(grp->hdcount), 2);
		hdoc = ft_strsplit(tmp3->heredoc, ';');
		while (hdoc[++i])
			if ((ret = heredoc(grp, file, hdoc[i])) < 0)
				break ;
		if (tmp3->file == NULL)
			tmp3->file = SDUP(file);
		REMOVE(&file);
		ft_freestrtab(&hdoc);
		if (ret < 0)
			return (-1);
	}
	return (0);
}

void		check_heredoc(t_group *grp)
{
	t_allcmd	*tmp;
	t_andor		*tmp2;
	t_parse		*tmp3;

	tmp = grp->allcmd;
	while (tmp)
	{
		tmp2 = tmp->andor;
		while (tmp2)
		{
			tmp3 = tmp2->parselst;
			while (tmp3)
			{
				if (prepare_heredoc(grp, tmp3) < 0)
					return ;
				tmp3 = tmp3->next;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
