/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:59:55 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/09 17:21:20 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include <stdio.h>

static void		insert_part(t_allcmd **lst, char *cmd)
{
	t_allcmd		*tmp;
	t_allcmd		*new;

	new = (t_allcmd *)malloc(sizeof(t_allcmd));
	new->cmd = ft_strtrim(cmd);
	//ft_strdel(&cmd);
	new->andor = NULL;
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

// void			display_lst(t_allcmd *lst)
// {
// 	t_allcmd *tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("cmd: %s\n", tmp->cmd);
// 		tmp = tmp->next;
// 	}
// }

static int		ft_wlen(char *s, int i, char c)
{
	int		len;
	int		synth;

	len = 0;
	synth = 0;
	while (s[i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && s[i] == c && (i > 0 && s[i - 1] != '\\'))
			break ;
		len++;
		i++;
	}
	check_parentheses(0);
	return (len);
}

t_allcmd		*ft_strsplitquote(char *s, char c)
{
	int		i;
	int		start;
	t_allcmd	*lst;
	char	*part;
	int		len;

	i = 0;
	start = 0;
	lst = NULL;
	len = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		start = i;
		len = ft_wlen(s, i, c);
		part = ft_strsub(s, start, len);
		if (part == NULL)
			return (NULL);
		else if (part[0] != '\0')
			insert_part(&lst, part);
		REMOVE(&part);
		i += len;
	}
	if (i == 0)
		return (NULL);
	check_parentheses(0);
	return (lst);
}
