/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 02:53:38 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/10 03:09:38 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		clean_checker(char **tmp, int errnb, int line)
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

int		update_last_ckecker(char **last, char *to_check)
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

/*
**	pour main checker :
**	=> add boucle checking( multi [[]]) 
*/

int		check_good_closure(char **check, int i)
{
	char	*last;

	if (ft_strncmp(check[i], "if", 2) == 0)
		last = ft_strdup("fi");
	else if (ft_strncmp("while", check[i], 5) == 0)
		last = ft_strdup("wi");
	i++;
	while (check[i])
	{
		if (ft_strncmp(check[i], "if", 2) == 0)
			last = ft_strjoin_nf("fi", last, 2);
		if (ft_strncmp(check[i], "while", 5) == 0 || ft_strncmp(check[i], "for ", 4) == 0)
			last = ft_strjoin_nf("wi", last, 2);
		if (ft_strcmp(check[i], "done") == 0)
		{
			if (update_last_ckecker(&last, "wi"))
				return (clean_checker(&last, E_INCOMPLETE_COND, -1));
			if (ft_strlen(last) == 0)
				return (clean_checker(&last, 0, -1));
		}
		if (ft_strcmp(check[i], "fi") == 0)
		{
			if (update_last_ckecker(&last, "fi"))
				return (clean_checker(&last, E_INCOMPLETE_COND, -1));
			if (ft_strlen(last) == 0)
				return (clean_checker(&last, 0, -1));		
		}
		i++;
	}
	if (ft_strlen(last))
		return (clean_checker(&last, E_INCOMPLETE_COND, -1));
	ft_strdel(&last);
	return (0);
}

int		check_comp_line(char *line)
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
	if (!(tmp = ft_strchr(line, '=')) && !(tmp = ft_strchr(line, '<')) && !(tmp = ft_strchr(line, '>')))
		return (1);
	if (*(tmp + 1) == '\0' || ft_strchr(tmp + 1, tmp[0]) || *(tmp - 1) == ' ' || *(tmp + 1) == ' ')
		return (1);
	if (ft_strlen(ft_strchr(line, '[')) - ft_strlen(ft_strchr(line, ']')) < 3)
		return (1);
	return (0);
}

// int		if_checker(char *tmp, char **check, int i)
// {
	
// }

int		assignation_checker(char *line)
{
	char	**clean;
	int		ret;

	ret = 0;
	clean = ft_strsplit(line, '=');
	if (!ft_strlen(clean[0]) || !clean[1] || !ft_strlen(clean[1]) || clean[2])
		ret = 1;
	if (ret == 0 && (ft_strchr(clean[1], ' ') && (clean[1][0] != '"' || LAST(clean[1]) != '"')))
		ret = 1;
	return (ret);
}

int		is_important_space(char *line)
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

int		for_loop_checker(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], "for ", 4))
			;
		i++;
	}
	return (0);
}

int		main_checker(char **check)
{
	int		i;
	char	*tmp;

	int		if_cnt;

	i = 0;
	if_cnt = 0;
	while (check[i])
	{
		tmp = ft_strtrim(check[i]);
		if (ft_strncmp(tmp, "if", 2) == 0)
		{
			if (ft_strncmp(tmp, "if [ ", 5) || !ft_strchr(tmp, ']') || !ft_strstr(tmp, " ]"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (check_good_closure(check, i))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (check_comp_line(tmp))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if_cnt++;
		}
		else if (ft_strncmp(tmp, "elif", 4) == 0)
		{
			if (ft_strncmp(tmp, "elif [ ", 7) || !ft_strchr(tmp, ']') || !ft_strstr(tmp, " ]"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (check_comp_line(tmp))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
		}
		else if (ft_strncmp(tmp, "else", 4) == 0)
		{
			if (ft_strcmp(tmp, "else"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 1] || ft_strcmp(check[i + 1], "then"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 2] || ft_strcmp(check[i + 2], "fi") == 0)
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
		}
		else if (ft_strcmp("fi", tmp) == 0)
			if_cnt--;
		else if (ft_strncmp("while", tmp, 5) == 0)
		{
			if (ft_strncmp(tmp, "while [ ", 8) || !ft_strchr(tmp, ']') || !ft_strstr(tmp, " ]"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 1] || ft_strcmp(check[i + 1], "do"))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (!check[i + 2] || ft_strcmp(check[i + 2], "done") == 0)
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (check_good_closure(check, i))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
			if (check_comp_line(tmp))
				return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
		}
		else if (ft_strchr(tmp, '=') && !is_important_space(tmp))
		{
			if (!(*(ft_strchr(tmp, '=') + 1) || ft_strchr(ft_strchr(tmp, '=') + 1, '=')))
				return (clean_checker(&tmp, E_TOO_EQU, i));
			if (ft_strstr(tmp, " =") || ft_strstr(tmp, "= "))
				return (clean_checker(&tmp, E_INSTANT, i));
			if (ft_strlen(tmp) == ft_strlen(ft_strchr(tmp, '=')))
				return (clean_checker(&tmp, E_INSTANT, i));
			if (assignation_checker(tmp))
				return (clean_checker(&tmp, E_INSTANT, i));

		}
		else if (ft_strncmp("for ", tmp, 4) && ft_strstr(tmp, " in "))
		{
			if (check_good_closure(check, i))
				return (clean_checker(&tmp, E_INVALID_LOOP, i));
		}
		ft_strdel(&tmp);
		i++;
	}
	if (if_cnt != 0)
		return (clean_checker(&tmp, E_INCOMPLETE_COND, i));
	return (0);
}