/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitandor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:16:37 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 18:00:57 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include <stdio.h>

int							ft_isandor(char *s, int idx)
{
	if (s[idx] == '&' && s[idx + 1] != '\0' && s[idx + 1] == '&')
		return (1);
	else if (s[idx] == '|' && s[idx + 1] != '\0' && s[idx + 1] == '|')
		return (2);
	return (0);
}

static void					insert_part(t_andor **lst, char *cmd, int type)
{
	t_andor		*tmp;
	t_andor		*new;

	new = (t_andor *)malloc(sizeof(t_andor));
	new->cmd = ft_strtrim(cmd);
	new->type = type;
	new->parselst = NULL;
	new->next = NULL;
	if (!*(lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int					ft_wlen(char *s, int i)
{
	int		len;
	int		synth;

	len = 0;
	synth = 0;
	while (s[i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && ft_isandor(s, i) > 0 && !check_last_char(s, i))
			break ;
		len++;
		i++;
	}
	check_parentheses(0);
	return (len);
}

static int					split_part(t_andor **lst, char *s, int i)
{
	int		type;
	int		len;
	int		start;
	char	*part;

	start = 0;
	len = 0;
	while ((type = (ft_isandor(s, i) > 0)) && !check_last_char(s, i))
	{
		if (i == 0)
			insert_part(lst, "", type);
		i += 2;
	}
	start = i;
	len = ft_wlen(s, i);
	i += len;
	part = ft_strsub(s, start, len);
	if (part == NULL)
		return (-1);
	type = ft_isandor(s, i);
	insert_part(lst, part, type);
	REMOVE(&part);
	return (i);
}

t_andor						*ft_strsplitandor(char *s)
{
	t_andor	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (s && s[i] != '\0')
	{
		i = split_part(&lst, s, i);
		if (i < 0)
			return (NULL);
	}
	if (i == 0)
		return (NULL);
	check_parentheses(0);
	return (lst);
}
