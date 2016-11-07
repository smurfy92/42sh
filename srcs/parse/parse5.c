/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:15:11 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/04 13:50:26 by jtranchi         ###   ########.fr       */
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

void		ft_addfile(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*tmp;

	start = i - 1;
	while (!ft_isalpha(parse->cmd[i]) && parse->cmd[i] &&
	!ft_is_quote(parse->cmd[i]) && parse->cmd[i] != '/')
		i++;
	end = i;
	while (parse->cmd[end] && !ft_end_of_red(parse->cmd[end]))
		end++;
	if (end == i)
	{
		grp->fail = 1;
		return (ft_putendl_fd("jush : parse error near `\\n'", 2));
	}
	tmp = ft_strsub(&parse->cmd[i], 0, end - i);
	parse->file = ft_strdup(tmp);
	parse->sgred = NULL;
	parse->dbred = NULL;
	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin(parse->cmd, tmp);
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

	tmp = ft_strjoin_nf(ft_strjoin("jush : parse error near `",
	&parse->cmd[end - 1]), "'", 1);
	ft_putendl_fd(tmp, 2);
	ft_strdel(&tmp);
}
