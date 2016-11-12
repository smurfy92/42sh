/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:18:21 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/11 16:22:45 by jtranchi         ###   ########.fr       */
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

void		ft_redirection_error(t_parse *parse, int end)
{
	char *tmp;

	tmp = ft_strjoin_nf(ft_strjoin("42sh : parse error near `",
	&parse->cmd[end - 1]), "'", 1);
	ft_putendl_fd(tmp, 2);
	ft_strdel(&tmp);
}