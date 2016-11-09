/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitandor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:16:37 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/09 17:21:11 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include <stdio.h>

int				ft_isandor(char *s, int idx)
{
	if (s[idx] == '&' && s[idx + 1] != '\0' && s[idx + 1] == '&')
		return (1);
	else if (s[idx] == '|' && s[idx + 1] != '\0' && s[idx + 1] == '|')
		return (2);
	return (0);
}

static void			insert_part(t_andor **lst, char *cmd, int type)
{
	t_andor		*tmp;
	t_andor		*new;

	new = (t_andor *)malloc(sizeof(t_andor));
	new->cmd = ft_strtrim(cmd);
	//ft_strdel(&cmd);
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

static int		ft_wlen(char *s, int i)
{
	int		len;
	int		synth;

	len = 0;
	synth = 0;
	while (s[i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && ft_isandor(s, i) > 0 && (i > 0 && s[i - 1] != '\\'))
			break ;
		len++;
		i++;
	}
	check_parentheses(0);
	return (len);
}

t_andor		*ft_strsplitandor(char *s)
{
	int		i;
	int		start;
	t_andor	*lst;
	char	*part;
	int		len;
	int		type;

	i = 0;
	start = 0;
	lst = NULL;
	len = 0;
	while (s && s[i] != '\0')
	{
		while (ft_isandor(s, i) > 0)
			i += 2;
		start = i;
		len = ft_wlen(s, i);
		i += len;
		part = ft_strsub(s, start, len);
		if (part == NULL)
			return (NULL);
		type = ft_isandor(s, i);
		insert_part(&lst, part, type);
		REMOVE(&part);
	}
	if (i == 0)
		return (NULL);
	check_parentheses(0);
	return (lst);
}
