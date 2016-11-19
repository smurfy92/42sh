/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:52:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/18 22:58:19 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in cmd_line at given indice
*/

static void		ft_polish_cmd_line(t_group *grp, int i)
{
	char	*tmp;

	if (TERM(cmd_line)[i + 2])
	{
		tmp = SDUP(&TERM(cmd_line)[i + 2]);
		TERM(cmd_line)[i + 1] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 3);
	}
	else
		TERM(cmd_line)[i + 1] = '\0';
}

/*
** polishing cmd_line by deleting unwanted charateres
** ex : escaped chars, separators
** checker l'utility des ! dans preparse sinon faire une fonction a part !
*/

static void		polish(t_group *grp)
{
	int ret;
	int test;
	int i;

	test = 0;
	i = -1;
	ft_pre_parse(grp);
	check_parentheses(0);
	while (TERM(cmd_line) && TERM(cmd_line)[++i])
	{
		ret = check_parentheses(TERM(cmd_line)[i]);
		if (TERM(cmd_line)[i] == '\\' &&
			TERM(cmd_line)[i + 1])
			ft_polish_cmd_line(grp, i - 1);
		if (test == 0 && ret == 1)
		{
			test = 1;
			ft_polish_cmd_line(grp, i - 1);
		}
		else if (test == 1 && ret == 0)
		{
			test = 0;
			ft_polish_cmd_line(grp, i - 1);
		}
	}
}

/*
** printing prompt for heredoc if has one or more
*/

void		heredoc(t_group *grp, char *file, char *eof)
{
	int		fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0755);
	free_term(grp);
	REMOVE(&TERM(cmd_line));
	check_parentheses(0);
	TERM(other_read) = true;
	while (TERM(other_read) == true)
	{
		grp->prompt_size = 7;
		ft_putstr("hdocs> ");
		get_cmd(grp, 0);
		polish(grp);
		if (TERM(cmd_line) && ft_strcmp(TERM(cmd_line), eof) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		free_term(grp);
		REMOVE(&TERM(cmd_line));
	}
	close(fd);
	TERM(other_read) = false;
}

/*
** checking if command has heredocs and activates heredoc prompt
*/

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
// afficher erreur parse after heredoc 