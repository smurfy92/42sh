/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:59:55 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/05 19:16:48 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		ft_cnt_parts(const char *s, char c)
{
	int		cnt;
	int		synth;
	int		in_part;
	int		idx;

	in_part = 0;
	synth = 0;
	cnt = 0;
	idx = 0;
	while (*s != '\0')
	{
		synth = check_parentheses(*s);
		if (synth == 0 && in_part == 1 && *s == c &&
			idx > 0 && *(s - 1) != '\\')
			in_part = 0;
		if (in_part == 0 && *s != c)
		{
			in_part = 1;
			cnt++;
		}
		s++;
		idx++;
	}
	check_parentheses(0);
	return (cnt);
}

static int		ft_wlen(const char *s, char c)
{
	int		len;
	int		synth;
	int		idx;

	len = 0;
	synth = 0;
	idx = 0;
	while (*s != '\0')
	{
		synth = check_parentheses(*s);
		if (synth == 0 && *s == c && idx > 0 && *(s - 1) != '\\')
			break ;
		len++;
		s++;
		idx++;
	}
	check_parentheses(0);
	return (len);
}

char			**ft_strsplitquote(char *s, char c)
{
	char	**t;
	int		nb_word;
	int		index;
	int		idx;

	index = 0;
	idx = 0;
	if (s == NULL)
		return (NULL);
	nb_word = ft_cnt_parts((const char *)s, c);
	t = (char **)malloc(sizeof(*t) * (nb_word + 1));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
		{
			if (idx > 0 && *(s - 1) != '\\')
				s++;
			idx++;
		}
		t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
		if (t[index] == NULL)
			return (NULL);
		s = s + ft_wlen(s, c);
		index++;
	}
	t[index] = NULL;
	check_parentheses(0);
	return (t);
}
