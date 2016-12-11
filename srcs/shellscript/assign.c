/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:51:42 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 17:05:08 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	cree une nouvelle action de type assignation
*/

/*
**	creee une nouvelle action => assignation de variable
*/

t_assign			*new_assignation(char *name, char *value)
{
	t_assign		*new;

	new = (t_assign *)malloc(sizeof(t_assign));
	new->name = ft_strtrim(name);
	new->value = ft_strtrim(value);
	return (new);
}

void				ft_my_trim(char **to_trim)
{
	char	*tmp;

	tmp = ft_strtrim(*to_trim);
	ft_strdel(to_trim);
	*to_trim = tmp;
}

/*
**	handler de l'assignation d'une variable, traite la chaine de caractere
**	de lassignation pour attribuer un type et une value a la var
*/

/*
**	deduit le type lors d'une assignation
*/

int					type_guesser(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (STR_T);
		i++;
	}
	return (NUMBER_T);
}

int					check_if_path(char *value)
{
	struct stat		buf;

	if (stat(value, &buf) < 0)
		return (1);
	return (0);
}

/*
**	make sure only one operation per assignation
*/

int					check_op(char *value)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if ((tmp = ft_strchr(value, '+')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '+')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '/')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '/')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '*')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '*')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '-')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '-')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '%')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '%')) ? ret += 2 : ret++;
	return (ret);
}
