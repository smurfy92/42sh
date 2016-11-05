/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitandor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:16:37 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/05 19:52:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

int				ft_isandor(char *s, int idx)
{
	if (s[idx] == '&' && s[idx + 1] != '\0' && s[idx + 1] == '&')
		return (1);
	else if (s[idx] == '|' && s[idx + 1] != '\0' && s[idx + 1] == '|')
		return (2);
	return (0);
}

void			insert_part(t_andor **lst, char *cmd, int type)
{
	t_andor		*tmp;
	t_andor		*new;

	new = (t_andor *)malloc(sizeof(t_andor));
	new->cmd = ft_strtrim(cmd);
	new->type = type;
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

void			display_lst(t_andor *lst)
{
	t_andor *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("cmd: %s -> %d\n", tmp->cmd, tmp->type);
		tmp = tmp->next;
	}
}

t_andor			*ft_strsplitandor(char *s)
{
	int		i;
	int		type;
	int		start;
	int		synth;
	t_andor	*lst;

	i = -1;
	start = 0;
	lst = NULL;
	while (s[++i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if ((type = ft_isandor(s, i)) > 0 && synth == 0)
		{
			if (i > 0 && s[i - 1] == '\\')
				continue ;
			insert_part(&lst, ft_strsub(s, start, i - start), type);
			start = i + 2;
			i++;
		}
	}
	insert_part(&lst, ft_strsub(s, start, i - start), type);
	display_lst(lst);
	check_parentheses(0);
	return (lst);
}
