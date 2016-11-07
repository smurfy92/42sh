/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:31:10 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/04 13:49:43 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_addredirectionsuite(t_parse *parse, int end, int start)
{
	char *tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
	ft_strdel(&tmp);
}

void		ft_adddoubleredirection(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;

	if (!parse->cmd[i])
	{
		grp->fail = 1;
		return (ft_putendl_fd("42sh : parse error near `\\n", 2));
	}
	start = i - 2;
	while (parse->cmd[i] && !ft_isalpha(parse->cmd[i]) &&
	!ft_isdigit(parse->cmd[i]) && !ft_is_quote(parse->cmd[i]) &&
	parse->cmd[i] != '/')
		i++;
	end = i;
	while (parse->cmd[end] && !ft_end_of_red(parse->cmd[end]))
		end++;
	if (end == i && (grp->fail = 1))
	{
		ft_redirection_error(parse, end);
		return ;
	}
	parse->dbred = ft_strsub(&parse->cmd[i], 0, end - i);
	ft_addredirectionsuite(parse, end, start);
}

void		ft_addredirection(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;

	if (!parse->cmd[i])
	{
		grp->fail = 1;
		return (ft_putendl_fd("42sh : parse error near `\\n'", 2));
	}
	start = i - 1;
	while (parse->cmd[i] && !ft_isalpha(parse->cmd[i]) &&
	!ft_isdigit(parse->cmd[i]) && !ft_is_quote(parse->cmd[i]) &&
	parse->cmd[i] != '/')
		i++;
	end = i;
	while ((parse->cmd[end] && !ft_end_of_red(parse->cmd[end])))
		end++;
	if (end == i && (grp->fail = 1))
	{
		ft_redirection_error(parse, end);
		return ;
	}
	parse->sgred = ft_strsub(&parse->cmd[i], 0, end - i);
	ft_addredirectionsuite(parse, end, start);
}

//a revoir

void		ft_addheredoc2(t_parse *parse, int end, int start)
{
	char	*tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
}

void		ft_addheredoc(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;
	char	*tmp;

	start = i - 2;
	int test = check_parentheses(parse->cmd[i]);
	while (!ft_isalpha(parse->cmd[i]) && parse->cmd[i])
		i++;
	end = i;
	while ((parse->cmd[end] && !ft_end_of_red(parse->cmd[end]) &&
	!ft_is_quote(parse->cmd[i])) ||
	(test == 0 && check_parentheses(parse->cmd[end])))
		end++;
	if (end == i)
	{
		grp->fail = 1;
		return (ft_putendl_fd("jush : parse error near `\\n'", 2));
	}
	tmp = ft_strsub(&parse->cmd[i], 0, end - i);
	if (!parse->heredoc)
	{
		parse->heredoc = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		parse->heredoc = ft_strjoin_nf(parse->heredoc,
		ft_strjoin_nf(";", tmp, 2), 3);
	ft_addheredoc2(parse, end, start);
}
