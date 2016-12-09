/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_make.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 22:46:53 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:09:50 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	appele lors du read des lines du script, pour bufferiser et recuperer
**	la string complete des conditions
*/

static int		end_of_condition(char *line)
{
	char	*tmp;
	tmp = ft_strtrim(line);
	if (ft_strncmp(line, "else", 4) == 0)
	{
		ft_strdel(&tmp);
		return (1);
	}
	if (ft_strncmp(line, "elif ", 5) == 0)
	{
		ft_strdel(&tmp);
		return (1);
	}
	if (ft_strncmp(line, "fi", 2) == 0)
	{
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

static int		cond_maker(char **clean, int i, t_script *script,
	t_cond **begin)
{
	char	*buff;
	char	str[2];
	int		last;

	last = 1;
	str_join_init(str);
	buff = ft_strdup(clean[i]);
	i++;
	while (clean[i])
	{
		if (ft_strncmp(clean[i], "if ", 3) == 0)
			last++;
		if (buff && end_of_condition(clean[i]) && last == 1)
		{
			new_cond(buff, script, begin);
			ft_strdel(&buff);
			return (0);
		}
		if (ft_strncmp(clean[i], "fi", 2) == 0)
			last--;
		buff = ft_strjoin_nf(ft_strjoin_nf(buff, str, 1), clean[i], 1);
		i++;
	}
	ft_strdel(&buff);
	return (E_INCOMPLETE_COND);
}

static	int		is_begin_cond(char *line)
{
	if (ft_strncmp(line, "if ", 3)== 0 ||
		ft_strncmp(line, "elif", 4) == 0 ||
		ft_strncmp(line, "else", 4) == 0)
		return (1);
	return (0);
}

static void		handle_end_of_cond(char *line, t_action **begin,
	t_cond **lead, t_script *script)
{
	if (ft_strlen(line) != 2)
			script->errno = E_INCOMPLETE_COND;
	new_cond(line, script, lead);
	add_to_action(*lead, script, COND_T, begin);
}

int				condition_maker(char *line, t_script *script, t_action **begin)
{
	char		**clean;
	int			i;
	int			last;
	t_cond		*lead;

	i = -1;
	last = 0;
	lead = NULL;
	clean = ft_strsplit(line, 135);
	while (clean[++i])
	{
		if (ft_strncmp(clean[i], "if ", 3) == 0)
			last++;
		if (is_begin_cond(clean[i]) && last == 1)
			cond_maker(clean, i, script, &lead);
		else if (ft_strncmp(clean[i], "fi", 2) == 0 && last == 1)
			handle_end_of_cond(clean[i], begin, &lead, script);
		if (ft_strncmp(clean[i], "fi", 2) == 0)
			last--;
	}
	ft_freestrtab(&clean);
	return (script->errno);
}