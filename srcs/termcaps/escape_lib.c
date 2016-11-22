/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:34:20 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/22 20:35:17 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		check_last_char(char *line, int i)
{
	char	*tmp;
	int		count;

	if (i == 0)
		return (0);
	tmp = &line[i - 1];
	count = 0;
	i--;
	while (*tmp == '\\')
	{
		count++;
		if (i == 0)
			break ;
		tmp = tmp - 1;
		i--;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

void	check_squote_escape(t_group *grp, int i, int *ret, int *test)
{
	if (*test == 0 && *ret == 1 && check_last_char(TERM(cmd_line), i) == 1)
	{
		*test = 1;
		*ret = 0;
	}
	else if (*test == 1 && *ret == 1)
		*test = 0;
}
