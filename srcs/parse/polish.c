/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:41:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/20 22:40:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** deletes char in parse cmd at given indice
*/

void		ft_polish_parse(t_parse *parse, int j, int i)
{
	parse->cmdsplit[j][i + 1] = '\0';
	if (parse->cmdsplit[j][i + 2])
	{
		parse->cmdsplit[j] = 
		JOINF(parse->cmdsplit[j], SDUP(&parse->cmdsplit[j][i + 2]), 3);
	}
}

void		polisher(t_parse *parse, int i, int j, int ret, int *in)
{
	char	q;

	if (*in == 0 && ret == 1)
	{
		q = parse->cmdsplit[j][i];
		ft_polish_parse(parse, j, i - 1);
		while ((q == '\'') && (ret = check_parentheses(parse->cmdsplit[j][i]))
		== 1 && parse->cmdsplit[j][i + 1] != '\'')
			i++;
		*in = 1;
	}
	else if (*in == 1 && ret == 0)
	{
		ft_polish_parse(parse, j, i - 1);
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
	int		j;

	in = 0;
	j = -1;
	check_parentheses(0);
	printf("CMD: %s\n", parse->cmd);
	while (parse->cmdsplit && parse->cmdsplit[++j])
	{
		i = -1;
		while (parse->cmdsplit[j][++i])
		{
			ret = check_parentheses(parse->cmdsplit[j][i]);
			if (ret == 0 && parse->cmdsplit[j][i] == '\\' &&
				parse->cmdsplit[j][i + 1])
				ft_polish_parse(parse, j, i - 1);
			else if (ret == 1 && parse->cmdsplit[j][i] == '\\' &&
				parse->cmdsplit[j][i + 1] && parse->cmdsplit[j][i + 1] == '\"')
				ft_polish_parse(parse, j, i - 1);
			polisher(parse, i, j, ret, &in);
		}
	}
}
