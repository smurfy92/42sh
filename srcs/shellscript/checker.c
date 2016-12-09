/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:32:48 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:10:30 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"


/*
**	envoie l'assignation a son action_maker
*/

static int			equal_checker(char *line,
	t_script *script, t_action **begin)
{
	char		**instant;
	t_assign	*new;

	if (ft_strchr(ft_strchr(line, '=') + 1, '='))
		return ((script->errnb = E_TOO_EQU));
	instant = ft_strsplit(line, '=');
	if (!instant[1])
		return ((script->errnb = E_INSTANT));
	new = new_assignation(instant[0], instant[1]);
	add_to_action(new, script, ASSIGN_T, begin);
	ft_freestrtab(&instant);
	return (0);
}

static int			cmd_checker(char *line, t_script *script, t_action **begin)
{
	t_line		*new;

	ft_putendl("HERE");
	new = (t_line *)malloc(sizeof(t_line));
	new->cmd = ft_strdup(line);
	ft_putendl("DONYDONE");
	add_to_action(new, script, LINE_T, begin);
	return (0);
}

/*
**	checke validite dune condition et bufferise 
**	toute la condition avant de l'envoyer a l'action maker
*/

static int			cond_checker(char **clean, int *i,
	t_script *script, char **line)
{
	char	*buff;
	char	str[2];
	int		last;

	(*i)++;
	str_join_init(str);
	*line = ft_strjoin_nf(*line, str, 1);
	last = 1;
	while (clean[*i])
	{
		buff = ft_strtrim(clean[*i]);
		buff = ft_strjoin_nf(buff, str, 1);
		*line = ft_strjoin_nf(*line, buff, 1);
		last = (ft_strncmp(buff, "if ", 3) == 0) ? last + 1 : last;
		last = (ft_strncmp(buff, "fi", 2) == 0) ? last - 1 : last;
		// if (ft_strncmp(buff, "if ", 3) == 0)
		// 	last++;
		// else if (ft_strncmp(buff, "fi", 2) == 0)
		// 	last--;
		if (ft_strncmp(buff, "fi", 2) == 0 && last == 0)
		{
			ft_strdel(&buff);
			return (0);
		}
		ft_strdel(&buff);
		(*i)++;
	}
	return ((script->errnb = E_INCOMPLETE_COND));
}

static int			loop_checker(char **clean, int *i, t_script *script,
	char **line)
{
	char	*buff;
	char	str[2];
	int		last;

	(*i)++;
	str_join_init(str);
	last = 1;
	*line = ft_strjoin_nf(*line, str, 1);
	while (clean[*i])
	{
		buff = ft_strtrim(clean[*i]);
		buff = ft_strjoin_nf(buff, str, 1);
		*line = ft_strjoin_nf(*line, buff, 1);
		if (ft_strncmp(buff, "while ", 6) == 0)
			last++;
		if (ft_strncmp(buff, "done", 4) == 0 && last == 1)
		{
			ft_strdel(&buff);
			return (0);
		}
		else if (ft_strncmp(buff, "done", 4) == 0)
			last--;
		ft_strdel(&buff);
		(*i)++;
	}
	return ((script->errnb = E_INCOMPLETE_COND));
}

/*
**	decide du bon handler a appele a la lecture dune ligne du script
*/

int					line_checker(char **clean, int *i, t_script *script, t_action **begin)
{
	char	*line;

	line = ft_strtrim(clean[*i]);
	if (ft_strncmp(line, "if ", 3) == 0)
	{
		if (!(script->errnb = cond_checker(clean, i, script, &line)))
			script->errnb = condition_maker(line, script, begin);
	}
	else if (ft_strncmp(line, "while ", 6) == 0)
	{
		if (!(script->errnb = loop_checker(clean, i, script, &line)))
			add_to_action(new_loop(line, script), script, LOOP_T, begin);
	}
	else if (ft_strchr(line, '=') && is_important_space(line))
		script->errnb = equal_checker(line, script, begin);
	else
		cmd_checker(line, script, begin);
	ft_strdel(&line);
	return (0);
}
