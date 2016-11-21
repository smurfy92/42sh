/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:18:21 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/21 04:45:42 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** check if char is a quote
*/

int			ft_is_quote(char c)
{
	if (c == '{' || c == '[' || c == '(' || c == '\'' || c == '"' || c == '`' ||
	c == ']' || c == ')' || c == '}')
		return (1);
	else
		return (0);
}

/*
** check if char is delimiter (space, tab, return line, etc...)
*/

int			ft_is_space(char c)
{
	if (c == '\t' || c == ' ' || c == '\v' || c == '\f' || c == '\r'
	|| c == '\n')
		return (1);
	else
		return (0);
}

/*
** check if char if and end of redirection
*/

int			ft_end_of_red(char c)
{
	if ((c == '\t' || c == ' ' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == '>' || c == '<' || c == '|') &&
		!check_parentheses(c))
		return (1);
	else
		return (0);
}
