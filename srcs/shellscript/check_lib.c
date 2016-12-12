/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 02:53:38 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 18:52:51 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				assignation_checker(char *line)
{
	char	**clean;
	int		ret;

	ret = 0;
	clean = ft_strsplit(line, '=');
	if (!ft_strlen(clean[0]) || !clean[1] || !ft_strlen(clean[1]) || clean[2])
		ret = 1;
	if (ret == 0 && (ft_strchr(clean[1], ' ') && (clean[1][0] != '"'
		|| LAST(clean[1]) != '"')))
		ret = 1;
	return (ret);
}

static char		*check_comp_helper(char *line)
{
	if (ft_strchr(line, '='))
	{
		if (ft_strchr(line, '<') || ft_strchr(line, '>'))
			return (NULL);
		return (ft_strchr(line, '='));
	}
	if (ft_strchr(line, '<'))
	{
		if (ft_strchr(line, '=') || ft_strchr(line, '>'))
			return (NULL);
		return (ft_strchr(line, '<'));
	}
	if (ft_strchr(line, '>'))
	{
		if (ft_strchr(line, '<') || ft_strchr(line, '='))
			return (NULL);
		return (ft_strchr(line, '>'));
	}
	return (NULL);
}

int				check_comp_line(char *line)
{
	char	*tmp;

	if (!(tmp = ft_strchr(line, '[')))
		return (1);
	if (*(tmp + 1) && ft_strchr(tmp + 1, '['))
		return (1);
	if (!(tmp = ft_strchr(line, ']')))
		return (1);
	if (*(tmp + 1) && ft_strchr(tmp + 1, ']'))
		return (1);
	if (!(tmp = check_comp_helper(line)))
		return (1);
	if (*(tmp + 1) == '\0' || ft_strchr(tmp + 1, tmp[0])
		|| *(tmp - 1) == ' ' || *(tmp + 1) == ' ')
		return (1);
	if (ft_strlen(ft_strchr(line, '[')) - ft_strlen(ft_strchr(line, ']')) < 3)
		return (1);
	return (0);
}

static int		check_helper(char **check, int *if_cnt, int i)
{
	char	*tmp;

	tmp = ft_strtrim(check[i]);
	if (ft_strncmp(tmp, "if", 2) == 0 && if_cond_checker(tmp, i, check))
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	else if (ft_strncmp(tmp, "if", 2) == 0)
		*if_cnt = *if_cnt + 1;
	else if (ft_strncmp(tmp, "elif", 4) == 0 &&
		elif_cond_checker(tmp, i, check))
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	else if (ft_strncmp(tmp, "else", 4) == 0 &&
		else_cond_checker(tmp, i, check))
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	else if (ft_strcmp("fi", tmp) == 0)
		*if_cnt = *if_cnt - 1;
	else if (ft_strncmp("while", tmp, 5) == 0 &&
		while_loop_checker(tmp, i, check))
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	else if (ft_strchr(tmp, '=') && !is_important_space(tmp) && ass_check(tmp))
		return (clean_checker(&tmp, E_INSTANT, i));
	else if (ft_strncmp("for ", tmp, 4) && ft_strstr(tmp, " in ") &&
		check_good_closure(check, i))
		return (clean_checker(&tmp, E_INVALID_LOOP, i));
	ft_strdel(&tmp);
	return (0);
}

int				main_checker(char **check)
{
	int		i;
	char	*tmp;
	int		if_cnt;
	int		ret;

	i = 0;
	if_cnt = 0;
	while (check[i])
	{
		if ((ret = check_helper(check, &if_cnt, i)))
			return (ret);
		i++;
	}
	if (if_cnt != 0)
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	return (0);
}
