/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:59:55 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/08 17:25:13 by julio            ###   ########.fr       */
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
	ft_strdel(&cmd);
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

t_allcmd		*ft_strsplitquote(char *s, char c)
{
	int		i;
	int		start;
	int		synth;
	t_allcmd	*lst;

	i = -1;
	start = 0;
	lst = NULL;
	while (s[++i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && s[i] == c)
		{
			if (i > 0 && s[i - 1] == '\\')
				continue ;
			insert_part(&lst, ft_strsub(s, start, i - start));
			start = i + 2;
			i++;
		}
	}
	insert_part(&lst, ft_strsub(s, start, i - start));
	//display_lst(lst);
	check_parentheses(0);
	return (lst);
}
