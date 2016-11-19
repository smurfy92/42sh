/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 21:49:53 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/19 21:53:02 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in parse cmd at given indice
*/

void		ft_polish_parse(t_parse *parse, int i)
{
	char	*tmp;

	if (parse->cmd[i + 2])
	{
		tmp = SDUP(&parse->cmd[i + 2]);
		parse->cmd[i + 1] = '\0';
		parse->cmd = JOINF(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i + 1] = '\0';
}

/*
** polishing parse by deleting unwanted charateres
** ex : escaped chars, separators
*/

void		polish(t_parse *parse)
{
	int		ret;
	int		test;
	int		i;
	char	q;

	test = 0;
	i = -1;
	check_parentheses(0);
	while (parse->cmd[++i])
	{
		ret = check_parentheses(parse->cmd[i]);
		if (parse->cmd[i] == '\\' &&
			parse->cmd[i + 1])
			ft_polish_parse(parse, i - 1);
		if (test == 0 && ret == 1 && (test = 1))
		{
			q = parse->cmd[i];
			ft_polish_parse(parse, i - 1);
			while ((q == '\'') &&(ret = check_parentheses(parse->cmd[i]))
			== 1 && parse->cmd[i + 1] != '\'')
				i++;
		}
		else if (test == 1 && ret == 0 && (test = 0))
			ft_polish_parse(parse, i - 1);
	}
}