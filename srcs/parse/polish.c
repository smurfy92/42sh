/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:41:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 22:41:51 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in parse cmd at given indice
*/

void		ft_polish_parse(t_parse *parse, int i)
{
	char	*tmp;

	parse->cmd[i + 1] = '\0';
	if (parse->cmd[i + 2])
		parse->cmd = JOINF(parse->cmd, SDUP(&parse->cmd[i + 2]), 3);
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
		if (test == 0 && ret == 1)
		{
			q = parse->cmd[i];
			ft_polish_parse(parse, i - 1);
			while ((q == '\'') &&(ret = check_parentheses(parse->cmd[i])) 
			== 1 && parse->cmd[i + 1] != '\'')
				i++;
			test = 1;
		}
		else if (test == 1 && ret == 0)
		{
			ft_polish_parse(parse, i - 1);
			test = 0;
		}
	}
}