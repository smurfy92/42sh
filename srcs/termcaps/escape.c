/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:35:14 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/03 18:24:22 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		check_last_char(char *line, int i)
{
	char	*tmp;
	int		count;

	if (i == 0)
		return (0);
	tmp = &line[i - 1];
	count = 0;
	i--;
	while (*tmp == '\\')
	{
		count++;
		if (i == 0)
			break ;
		tmp = tmp - 1;
		i--;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int		check_esc(t_group *grp)
{
	int		i;
	int		ret;
	char	c;

	i = -1;
	ret = -1;
	while (TERM(cmd_line) && (c = TERM(cmd_line)[++i]) != '\0')
	{
		if ((c == '"' || c == '`' || c =='\'') && check_last_char(TERM(cmd_line), i) == 0)
			ret = check_parentheses(c);
		else if (c != '"' && c != '`' && c != '\'')
			if ((ret = check_parentheses(c)) < 0)
				return (-1);
	}
	if (TERM(cmd_line) && c == '\0' && check_last_char(TERM(cmd_line), i) == 1)
		return (1);
	else if (ret == -1 && TERM(cmd_quote) != NULL &&
		check_parentheses('o') == 0)
		return (0);
	else if (TERM(cmd_line) == NULL && TERM(cmd_quote) == NULL)
		return (0);
	return (ret);
}

void	fill_cmdquote(t_group *grp)
{
	t_cmdquote	*line;
	t_cmdquote	*tmp;

	tmp = TERM(cmd_quote);
	line = (t_cmdquote *)malloc(sizeof(t_cmdquote));
	line->line = TERM(cmd_line) ? SDUP(TERM(cmd_line)) : SDUP("");
	line->next = NULL;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = line;
	else
		TERM(cmd_quote) = line;
	TERM(curs_pos) = 0;
	TERM(line) = 0;
	TERM(cmd_size) = 0;
	TERM(other_read) = 0;
	REMOVE(&TERM(cmd_line));
}

void	fill_cmd_line(t_group *grp)
{
	t_cmdquote *tmp;

	fill_cmdquote(grp);
	tmp = TERM(cmd_quote);
	TERM(cmd_line) = SDUP("");
	while (tmp)
	{
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp->line, 1);
		if (tmp->next)
			TERM(cmd_line) = JOINF(TERM(cmd_line), "\n", 1);
		tmp = tmp->next;
	}
}

int		ft_escape(t_group *grp)
{
	int	ret;

	if ((ret = check_esc(grp)) == 0)
	{
		grp->prompt_size = 6;
		return (0);
	}
	// else if (ret < 0)
	// 	return (ret);
	fill_cmdquote(grp);
	ft_putstr("\n$>");
	grp->prompt_size = 2;
	return (1);
}
