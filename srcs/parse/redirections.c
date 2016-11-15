/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:10:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/15 15:35:46 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_addfile(t_group *grp, t_parse *parse, int i)
{
	if (parse->file)
		REMOVE(&parse->file);
	parse->file = get_redirection(grp, parse, i,  i - 1);
	check_rights(parse, &parse->file, 1);
}

static void		ft_adddoubleredirection(t_group *grp, t_parse *parse, int i)
{
	if (parse->dbred)
		REMOVE(&parse->dbred);
	parse->dbred = get_redirection(grp, parse, i,  i - 2);
	if (check_rights(parse, &parse->dbred, 0))
		grp->fail = 1;
}

static void		ft_addredirection(t_group *grp, t_parse *parse, int i)
{
	if (parse->sgred)
		REMOVE(&parse->sgred);
	parse->sgred = get_redirection(grp, parse, i, i - 1);
	if (check_rights(parse, &parse->sgred, 0))
		grp->fail = 1;
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