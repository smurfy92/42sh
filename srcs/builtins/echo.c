/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:03:39 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/18 18:16:28 by jmontija         ###   ########.fr       */
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

int		ft_power(int nb, int power)
{
	int total;

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

int convertOctalToDecimal(int octalNumber)
{
	int	decimalNumber;
	int	i;

	i = 0;
	decimalNumber = 0;
	while(octalNumber != 0)
	{
		decimalNumber += (octalNumber%10) * ft_power(8,i);
		++i;
		octalNumber/=10;
	}
	return decimalNumber;
}

int		replace_ascii(char c, char *str, char **ptr)
{
	int		i;
	int		decimal_int;
	char	*octal_char;

	i = 0;
	octal_char = NEW(0);
	while (ft_isdigit(str[i]))
	{
		if (i == 2)
		{
			if (ft_atoi(&str[i]) < 8)
			{
				octal_char = ft_charjoin(octal_char, str[i]);
				i++;
			}
			break ;
		}
		octal_char = ft_charjoin(octal_char, str[i]);
		i++;
	}
	printf("YO %s\n", octal_char);
	decimal_int = convertOctalToDecimal(ft_atoi(octal_char));
	(*ptr) += i;
	return (decimal_int);
}

char	check_operands(char c, char *str, char **ptr)
{
	if (c == 'a')
	{
		tputs(tgetstr("bl", NULL), 0, ft_getchar);
		return (c);
	}
	else if (c == 'b')
		return ('\b');
	else if (c == 'c')
		return ('\0');
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
	{
		(*ptr) += 1;
		return (c);
	}
	else if (c == '0')
		return (replace_ascii(c, str, ptr));
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
		if (arg[i] == '\\' && arg[i + 1] != '\0' && (operand = check_operands(arg[i + 1], &arg[i + 2], &arg)) >= 0)
		{
			if (operand == '\0')
				break ;
			if (operand != 'a')
			{
				tmp = new;
				new = ft_charjoin(tmp, operand);
				REMOVE(&tmp);
			}
			i++;
			// if (operand != '\\')
			// 	i++;
			// else
			// 	i += 2;
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
