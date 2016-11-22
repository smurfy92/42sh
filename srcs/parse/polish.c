/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:41:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/22 03:48:04 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_replace_dolls(t_group *grp, t_parse *parse, int j, int i)
{
	int		start;
	char	*tmp;
	char	*tmp2;

	start = i;
	while (parse->cmdsplit[j][i] && (ft_isalpha(parse->cmdsplit[j][i]) || parse->cmdsplit[j][i] == '?'))
		i++;
	tmp = ft_strsub(&parse->cmdsplit[j][start], 0, i - start);
	tmp2 = ft_strdup(&parse->cmdsplit[j][i]);
	if (ft_strlen(tmp) == 1 && tmp[0] == '?')
		ft_replace_dollar(grp, parse, tmp2, start);
	else if (ft_getenv(grp, tmp) == NULL)
		grp->minus = 1;
	else
	{
		parse->cmdsplit[j][start - 1] = '\0';
		if (!parse->cmdsplit[j][start + 1])
			parse->cmdsplit[j] = ft_strjoin_nf(parse->cmdsplit[j], ft_getenv(grp, tmp), 1);
		else
			parse->cmdsplit[j] = JOINF(JOINF(parse->cmdsplit[j],
			ft_getenv(grp, tmp), 1), tmp2, 1);
		ft_strdel(&tmp2);
	}
	(tmp) ? REMOVE(&tmp) : 0;
	(tmp2) ? REMOVE(&tmp2) : 0;

}

void		ft_polish_parse(t_parse *parse, int j, int i)
{
	parse->cmdsplit[j][i] = '\0';
	if (parse->cmdsplit[j][i + 1])
	{
		parse->cmdsplit[j] = 
		JOINF(parse->cmdsplit[j], SDUP(&parse->cmdsplit[j][i + 1]), 3);
	}
}

void		handle_squote(t_parse *parse, int j, int *i)
{
	ft_polish_parse(parse, j, *i);
	while (parse->cmdsplit[j][*i] != '\'' && parse->cmdsplit[j][*i] != '\0')
		*i += 1;
	if (parse->cmdsplit[j][*i] == '\'')
		ft_polish_parse(parse, j, *i);
}

void		handle_dquote(t_parse *parse, int j, int *i)
{
	t_group *grp;
	char c;

	grp = get_grp();
	ft_polish_parse(parse, j, *i);
	while (parse->cmdsplit[j][*i] != '\0' &&
		(parse->cmdsplit[j][*i] != '"' || check_last_char(parse->cmdsplit[j], *i) == 1))
	{
		c = parse->cmdsplit[j][*i];
		if (c == '$' && check_last_char(parse->cmdsplit[j], *i) == 0)
			ft_replace_dolls(grp, parse, j, *i + 1);
		else if (c == '$' && check_last_char(parse->cmdsplit[j], *i) == 1)
		{
			ft_polish_parse(parse, j, *i - 1);
			*i -= 1;
		}
		if (c == '"' && check_last_char(parse->cmdsplit[j], *i) == 1)
		{
			ft_polish_parse(parse, j, *i - 1);
			*i -= 1;
		}
		*i += 1;
	}
	if (parse->cmdsplit[j][*i] == '"')
		ft_polish_parse(parse, j, *i);
}

void		polish(t_parse *parse)
{
	int		ret;
	int		in;
	int		i;
	int		j;

	in = 0;
	j = -1;
	check_parentheses(0);
	while (parse->cmdsplit && parse->cmdsplit[++j])
	{
		i = -1;
		while (parse->cmdsplit[j][++i])
		{
			ret = check_parentheses(parse->cmdsplit[j][i]);
			if (ret == 1 && parse->cmdsplit[j][i] == '\'')
				handle_squote(parse, j, &i);
			else if (ret == 1 && parse->cmdsplit[j][i] == '\"')
				handle_dquote(parse, j, &i);
			else if (ret == 0 && parse->cmdsplit[j][i] == '\\' && parse->cmdsplit[j][i + 1])
				ft_polish_parse(parse, j, i);
		}
	}
}
