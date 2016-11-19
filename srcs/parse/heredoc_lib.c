/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:32:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 20:45:24 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in cmd_line at given indice
*/

void		ft_polish_hd_line(t_group *grp, int i)
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
*/

void		polish_hd(t_group *grp)
{
	int	ret;
	int	test;
	int	i;

	test = 0;
	i = -1;
	ft_pre_parse(grp);
	check_parentheses(0);
	while (TERM(cmd_line) && TERM(cmd_line)[++i])
	{
		ret = check_parentheses(TERM(cmd_line)[i]);
		if (TERM(cmd_line)[i] == '\\' &&
			TERM(cmd_line)[i + 1])
			ft_polish_hd_line(grp, i - 1);
		if (test == 0 && ret == 1)
		{
			test = 1;
			ft_polish_hd_line(grp, i - 1);
		}
		else if (test == 1 && ret == 0)
		{
			test = 0;
			ft_polish_hd_line(grp, i - 1);
		}
	}
}
