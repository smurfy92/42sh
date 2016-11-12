/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:10:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 18:47:21 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_addredirectionsuite(t_parse *parse, int end, int start)
{
	char *tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
	ft_strdel(&tmp);
}

static void		ft_adddoubleredirection(t_group *grp, t_parse *parse, int i)
{
	int		start;
	int		end;

	if (!parse->cmd[i])
	{
		grp->fail  = 1;
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

static void		ft_addredirection(t_group *grp, t_parse *parse, int i)
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

static void		ft_parse_redirections2(t_group *grp, t_parse *parse, int i)
{
	if (ft_isdigit(parse->cmd[i]) && parse->cmd[i + 1] == '>' &&
	parse->cmd[i + 2] == '&' && parse->cmd[i + 3] && parse->cmd[i + 3] == '-')
		ft_check_close(parse, i);
	else if (ft_isdigit(parse->cmd[i]) && parse->cmd[i + 1] == '>' &&
	parse->cmd[i + 2] == '&' && parse->cmd[i + 3] &&
	ft_isdigit(parse->cmd[i + 3]))
		ft_check_redirection_fd(parse, i);
	else if (parse->cmd[i] == '>' && parse->cmd[i + 1] &&
	parse->cmd[i + 1] == '>')
		ft_adddoubleredirection(grp, parse, i + 2);
	else if (parse->cmd[i] == '>')
		ft_addredirection(grp, parse, i + 1);
	else if (parse->cmd[i] == '<' && parse->cmd[i + 1] &&
	parse->cmd[i + 1] == '<')
		ft_addheredoc(parse, i + 2);
	else if (parse->cmd[i] == '<')
		ft_addfile(grp, parse, i + 1);
	else if (parse->cmd[i] == '$' && parse->cmd[i + 1])
		ft_replace_vars(grp, parse, i + 1);
	else if (parse->cmd[i] == '~')
		ft_replace_tilde(grp, parse, i);
	else
		grp->minus = 1;
}

void		ft_parse_redirections(t_group *grp, t_parse *parse)
{
	int i;
	int ret;

	i = 0;
	check_parentheses(0);
	while (parse->cmd[i])
	{
		grp->minus = 0;
		ret = check_parentheses(parse->cmd[i]);
		if (!ret && (i == 0 || parse->cmd[i - 1] != '\\'))
			ft_parse_redirections2(grp, parse, i);
		else
			i++;
		if (grp->fail || parse->fail)
			break ;
		if (parse->sgred || parse->dbred)
			ft_create_redirections(parse);
		if (grp->minus)
			i++;
	}
}