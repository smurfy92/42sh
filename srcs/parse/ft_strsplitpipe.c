/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitpipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:59:55 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/09 19:32:21 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include <stdio.h>

static void			insert_part(t_andor **lst, char *cmd)
{
	t_andor		*tmp;
	t_andor		*new;

	new = (t_andor *)malloc(sizeof(t_andor));
	new->cmd = ft_strtrim(cmd);
	new->type = 0;
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

static int		ft_wlen(char *s, int i, char c)
{
	int		len;
	int		synth;

	len = 0;
	synth = 0;
	while (s[i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && s[i] == c && !check_last_char(s, i))
			break ;
		len++;
		i++;
	}
	check_parentheses(0);
	return (len);
}

t_andor		*ft_strsplitpipe(char *s, char c)
{
	int		i;
	int		start;
	t_andor	*lst;
	char	*part;
	int		len;

	i = 0;
	start = 0;
	lst = NULL;
	len = 0;
	while (s && s[i] != '\0')
	{


		while (s[i] == c && !check_last_char(s, i))
		{
			if (i == 0)
				insert_part(&lst, "");
			i++;
		}
		start = i;
		len = ft_wlen(s, i, c);
		part = ft_strsub(s, start, len);
		if (part == NULL)
			return (NULL);
		insert_part(&lst, part);
		REMOVE(&part);
		i += len;
	}
	if (i == 0)
		return (NULL);
	check_parentheses(0);
	return (lst);
}
