/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:28:59 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 18:41:04 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		if_cond_checker(char *tmp, int i, char **check)
{
	if (ft_strncmp(tmp, "if [ ", 5) || !ft_strchr(tmp, ']') ||
		!ft_strstr(tmp, " ]"))
		return (1);
	if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
		return (1);
	if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
		return (1);
	if (check_good_closure(check, i))
		return (1);
	if (check_comp_line(tmp))
		return (1);
	return (0);
}

int		elif_cond_checker(char *tmp, int i, char **check)
{
	if (ft_strncmp(tmp, "elif [ ", 7) || !ft_strchr(tmp, ']') ||
		!ft_strstr(tmp, " ]"))
		return (1);
	if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
		return (1);
	if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
		return (1);
	if (check_comp_line(tmp))
		return (1);
	return (0);
}

int		else_cond_checker(char *tmp, int i, char **check)
{
	if (ft_strcmp(tmp, "else"))
		return (1);
	if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
		return (1);
	if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
		return (1);
	return (0);
}

int		while_loop_checker(char *tmp, int i, char **check)
{
	if (ft_strncmp(tmp, "while [ ", 8) || !ft_strchr(tmp, ']') ||
		!ft_strstr(tmp, " ]"))
		return (1);
	if (!check[i + 1] || ft_strcmp(check[i + 1], "do"))
		return (1);
	if (!check[i + 2] || ft_strcmp(check[i + 2], "done") == 0)
		return (1);
	if (check_good_closure(check, i))
		return (1);
	if (check_comp_line(tmp))
		return (1);
	return (0);
}

int		ass_check(char *tmp)
{
	if (!(*(ft_strchr(tmp, '=') + 1) ||
		ft_strchr(ft_strchr(tmp, '=') + 1, '=')))
		return (1);
	if (ft_strstr(tmp, " =") || ft_strstr(tmp, "= "))
		return (1);
	if (ft_strlen(tmp) == ft_strlen(ft_strchr(tmp, '=')))
		return (1);
	if (assignation_checker(tmp))
		return (1);
	return (0);
}
