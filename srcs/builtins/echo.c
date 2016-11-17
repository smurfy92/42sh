/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:03:39 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/17 20:01:35 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char	*ft_charjoin(char *s1, char c)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s1) + 1;
	new = ft_strnew(size);
	new = ft_strcpy(new, s1);
	new[size - 1] = c;
	new[size] = '\0';
	return (new);
}

char	check_operands(char c)
{
	if (c == 'a')
	{

	}
	else if (c == 'b')
		return ('\b');
	else if (c == 'c')
	{

	}
	else if (c == 'f')
		return ('\f');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return (c);
	else if (c == '0')
	{
		//this char is a number to transform on char
		//write the char corresponding to the ascii value
	}
	return (-1);
}

void	check_line(char *arg)
{
	int		i;
	char	operand;
	char	*new;
	char	*tmp;

	i = -1;
	new = NEW(0);
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\\' && arg[i + 1] != '\0' && (operand = check_operands(arg[i + 1])) >= 0)
		{
			tmp = new;
			new = ft_charjoin(tmp, operand);
			REMOVE(&tmp);
			if (operand != '\\')
				i++;
			else
				i += 2;
		}
		else
			new = ft_charjoin(new, arg[i]);
	}
	ft_putstr(new);
}

int		builtin_echo(t_group *grp, t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->cmdsplit[++i])
		check_line(parse->cmdsplit[i]);
	ft_putchar('\n');
	return (1);
}
