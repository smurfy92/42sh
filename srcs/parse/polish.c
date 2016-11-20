/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:41:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 23:46:51 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in parse cmd at given indice
*/

void		ft_polish_parse(t_parse *parse, int i)
{
	parse->cmd[i + 1] = '\0';
	if (parse->cmd[i + 2])
		parse->cmd = JOINF(parse->cmd, SDUP(&parse->cmd[i + 2]), 3);
}

void		polisher(t_parse *parse, int i, int ret, int *in)
{
	char	q;

	if (*in == 0 && ret == 1)
	{
		q = parse->cmd[i];
		ft_polish_parse(parse, i - 1);
		while ((q == '\'') && (ret = check_parentheses(parse->cmd[i]))
		== 1 && parse->cmd[i + 1] != '\'')
			i++;
		*in = 1;
	}
	else if (*in == 1 && ret == 0)
	{
		ft_polish_parse(parse, i - 1);
		*in = 0;
	}
}

/*
** polishing parse by deleting unwanted charateres
** ex : escaped chars, separators
*/

void		polish(t_parse *parse)
{
	int		ret;
	int		in;
	int		i;

	i = -1;
	in = 0;
	check_parentheses(0);
	while (parse->cmd[++i])
	{
		ret = check_parentheses(parse->cmd[i]);
		if (parse->cmd[i] == '\\' && parse->cmd[i + 1])
			ft_polish_parse(parse, i - 1);
		polisher(parse, i, ret, &in);
	}
}
