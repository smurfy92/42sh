/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:18:21 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 00:22:08 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			ft_is_quote(char c)
{
	if (c == '{' || c == '[' || c == '(' || c == '\'' || c == '"' || c == '`' ||
	c == ']' || c == ')' || c == '}')
		return (1);
	else
		return (0);
}

int			ft_is_space(char c)
{
	if (c == '\t' || c == ' ' || c == '\v' || c == '\f' || c == '\r'
	|| c == '\n')
		return (1);
	else
		return (0);
}

int			ft_end_of_red(char c)
{
	if ((c == '\t' || c == ' ' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == '>' || c == '<' || c == '|') &&
		!check_parentheses(c))
		return (1);
	else
		return (0);
}
