/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:57:57 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 16:55:43 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include "math.h"

/*
**	could be put in libft !
**	a revoir ft_power ne marche pas comme il faut !
*/

char	*ft_charjoin(char *s1, char c)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s1) + 1;
	new = ft_strnew(size);
	new = ft_strcpy(new, s1);
	new[size - 1] = c;
	new[size] = '\0';
	REMOVE(&s1);
	return (new);
}

int		ft_power(int nb, int power)
{
	int	total;

	total = nb;
	if (power > 1)
	{
		while (power > 1)
		{
			total = total * nb;
			power--;
		}
	}
	else if (power == 0)
		return (1);
	else
		return (0);
	return (total);
}

int		octal_to_decimal(int octal_nb)
{
	int	decimal_nb;
	int	i;

	i = 0;
	decimal_nb = 0;
	while (octal_nb != 0)
	{
		decimal_nb += (octal_nb % 10) * pow(8, i);
		++i;
		octal_nb /= 10;
	}
	return (decimal_nb);
}
