/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:10:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/23 22:39:42 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** checking if it is a redirection at given indice
** and sending to correct function if true
*/

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
		ft_addheredoc(grp, parse, i + 2);
	else if (parse->cmd[i] == '<')
		ft_addfile(grp, parse, i + 1);
	else if (parse->cmd[i] == '$' && parse->cmd[i + 1])
		ft_replace_vars(grp, parse, i + 1);
	else if (parse->cmd[i] == '~')
		ft_replace_tilde(grp, parse, i);
	else
		grp->minus = 1;
}

/*
** checking parse cmd char by char to parse redirections
*/

void			ft_parse_redirections(t_group *grp, t_parse *parse)
{
	int i;
	int ret;
	int	inquote;

	i = 0;
	(inquote = false) ? check_parentheses(0) : check_parentheses(0);
	while (parse->cmd[i])
	{
		grp->minus = 0;
		ret = check_parentheses(parse->cmd[i]);
		(inquote == parse->cmd[i]) ? (inquote = false) : 0;
		(!inquote && ret && parse->cmd[i] != '`') ?
		(inquote = parse->cmd[i]) : 0;
		if (!ret && (i == 0 || parse->cmd[i - 1] != '\\'))
			ft_parse_redirections2(grp, parse, i);
		else if (ret && !inquote && parse->cmd[i] == '`' &&
				check_last_char(parse->cmd, i) == 0)
			ft_replace_bquote(parse, i);
		else
			i++;
		if (grp->fail || parse->fail)
			break ;
		(grp->minus) ? (i += 1) : 0;
	}
}
