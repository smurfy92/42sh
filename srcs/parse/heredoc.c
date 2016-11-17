/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:52:49 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 16:48:38 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_polish_parse(t_group *grp, int i)
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

static void		polish(t_group *grp)
{
	int ret;
	int test;
	int i;

	test = 0;
	i = -1;
	ft_pre_parse(grp); // checker l'utility des ! dans preparse sinon faire une fonction a part !
	check_parentheses(0);
	while (TERM(cmd_line) && TERM(cmd_line)[++i])
	{
		ret = check_parentheses(TERM(cmd_line)[i]);
		if (TERM(cmd_line)[i] == '\\' &&
			TERM(cmd_line)[i + 1])
			ft_polish_parse(grp, i - 1);
		if (test == 0 && ret == 1)
		{
			test = 1;
			ft_polish_parse(grp, i - 1);
		}
		else if (test == 1 && ret == 0)
		{
			test = 0;
			ft_polish_parse(grp, i - 1);
		}
	}
}

void		heredoc(t_group *grp, char *file, char *eof)
{
	int		fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0755);
	free_term(grp);
	REMOVE(&TERM(cmd_line));
	check_parentheses(0);
	while (42)
	{
		TERM(other_read) = true;
		grp->prompt_size = 6;
		ft_putstr("hdocs>");
		get_cmd(grp, 0);
		polish(grp);
		if (TERM(cmd_line) && ft_strcmp(TERM(cmd_line), eof) == 0)
			break ;
		ft_putendl_fd(TERM(cmd_line), fd);
		free_term(grp);
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