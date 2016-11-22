/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:03:39 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/22 19:45:32 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		replace_ascii(char *str, char **ptr)
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
	decimal_int = octal_to_decimal(ft_atoi(octal_char));
	(*ptr) += i;
	REMOVE(&octal_char);
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
		return ('\\');
	else if (c == '0')
		return (replace_ascii(str, ptr));
	return (-1);
}

int	check_line(char *arg)
{
	int		i;
	char	operand;

	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\\' && arg[i + 1] != '\0' && !check_last_char(arg, i) &&
			(operand = check_operands(arg[i + 1], &arg[i + 2], &arg)) >= 0)
		{
			if (operand == '\0')
			{
				return (1);
			}
			if (operand != 'a')
				ft_putchar(operand);
			i++;
		}
		else
			ft_putchar(arg[i]);
	}
	return (0);
}


int		builtin_echo(t_group *grp, t_parse *parse)
{
	int	i;
	int	ret;

	i = 0;
	while (grp && parse->cmdsplit[++i])
	{
		ret = check_line(parse->cmdsplit[i]);
		if (parse->cmdsplit[i + 1])
			ft_putchar(' ');
	}
	if (!ret)
		ft_putchar('\n');
	else
	{
		tputs(tgetstr("so", NULL), 0, ft_getchar);
		ft_putstr("%\n");
		tputs(tgetstr("se", NULL), 0, ft_getchar);
	}
	return (1);
}
