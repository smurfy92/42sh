/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:18:21 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/11 16:46:11 by vdanain          ###   ########.fr       */
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

/*
** replacing tilde in parse cmd
*/

void		ft_replace_tilde(t_group *grp, t_parse *parse, int i)
{
	char	*path;
	char	*tmp;

	path = ft_getenv(grp, "HOME");
	if (path == NULL)
		ft_putendl_fd("Your stupid theres no home", 2);
	tmp = SDUP(&parse->cmd[i + 1]);
	parse->cmd[i] = '\0';
	if (parse->cmd[i + 1])
	{
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
	}
	else
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
	REMOVE(&tmp);
	grp->minus = 1;
}
