/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:35:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 18:52:34 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				clean_checker(char **tmp, int errnb, int line)
{
	if (tmp)
		ft_strdel(tmp);
	get_script(NULL)->errnb = errnb;
	if (errnb && line != -1)
	{
		ft_putstr_fd("Error on line ", 2);
		ft_putnbr_fd(line + 1, 2);
		ft_putstr_fd(": ", 2);
	}
	return (errnb);
}

int				update_last_checker(char **last, char *to_check)
{
	char	*tmp;
	int		len;

	if (ft_strncmp(*last, to_check, 2))
	{
		return (1);
	}
	if ((len = ft_strlen(*last)) > 2)
		tmp = ft_strsub(*last, 2, len - 2);
	else
		tmp = ft_strdup("");
	ft_strdel(last);
	*last = tmp;
	return (0);
}

static int		closure_helper(char **check, char **last, int i)
{
	if (ft_strncmp(check[i], "if", 2) == 0)
		*last = ft_strjoin_nf("fi", *last, 2);
	if (ft_strncmp(check[i], "while", 5) == 0 ||
		ft_strncmp(check[i], "for ", 4) == 0)
		*last = ft_strjoin_nf("wi", *last, 2);
	if (ft_strcmp(check[i], "done") == 0)
	{
		if (update_last_checker(last, "wi"))
			return (E_INCOMPLETE_COND);
		if (ft_strlen(*last) == 0)
			return (clean_checker(last, 0, -1));
	}
	if (ft_strcmp(check[i], "fi") == 0)
	{
		if (update_last_checker(last, "fi"))
			return (E_INCOMPLETE_COND);
		if (ft_strlen(*last) == 0)
			return (0);
	}
	return (0);
}

int				is_important_space(char *line)
{
	int		i;
	int		ret;

	check_parentheses(0);
	i = 0;
	while (line[i])
	{
		ret = check_parentheses(line[i]);
		if (ret == 0 && line[i] == ' ')
			return (1);
		i++;
	}
	check_parentheses(0);
	return (0);
}

/*
**	pour main checker :
**	=> add boucle checking( multi [[]])
*/

int				check_good_closure(char **check, int i)
{
	char	*last;

	if (ft_strncmp(check[i], "if", 2) == 0)
		last = ft_strdup("fi");
	else if (ft_strncmp("while", check[i], 5) == 0)
		last = ft_strdup("wi");
	i++;
	while (check[i])
	{
		if (closure_helper(check, &last, i))
		{
			ft_strdel(&last);
			return (E_INCOMPLETE_COND);
		}
		i++;
	}
	if (ft_strlen(last))
		return (clean_checker(&last, E_INCOMPLETE_COND, -1));
	ft_strdel(&last);
	return (0);
}
