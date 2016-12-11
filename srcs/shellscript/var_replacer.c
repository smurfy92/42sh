/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 03:52:23 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 19:17:30 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	appele lors du reading d'actions, ces fonctions sont utilisees pour
**	remplacer les var par leur val dans les chaines
*/

static int		len_to_space(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

void			ft_strreplace(char **line, char *old, char *new)
{
	char	*tmp;
	char	*new_line;
	int		len;

	tmp = ft_strstr(*line, old);
	len = ft_strlen(*line) - ft_strlen(tmp);
	new_line = ft_strsub(*line, 0, len - 1);
	new_line = ft_strjoin_nf(new_line, new, 1);
	new_line = ft_strjoin_nf(new_line, tmp + ft_strlen(old), 1);
	ft_strdel(line);
	*line = ft_strdup(new_line);
	ft_strdel(&new_line);
}

static void		replace_at(char **line, int i, t_script *script)
{
	int		len;
	char	*old;
	t_var	*var;
	char	*new;
	char	*tmp;

	tmp = *line;
	len = len_to_space(&tmp[i]);
	old = ft_strsub(&tmp[i], 0, len);
	if (!(var = check_if_var_exists(old, script)) &&
		!(ft_getenv(get_grp(), old)))
	{
		script->errnb = E_UNKNOWN_VAR;
		ft_strdel(&old);
		error_handler(script);
	}
	if (ft_getenv(get_grp(), old))
		new = ft_strdup(ft_getenv(get_grp(), old));
	else if (var->type == STR_T)
		new = ft_strdup(var->str);
	else
		new = ft_itoa(*var->nb);
	ft_strreplace(line, old, new);
	ft_strdel(&old);
	ft_strdel(&new);
}

void			var_replacer(t_script *script, char **line)
{
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] != '\0' &&
			(*line)[i + 1] != ' ' && (*line)[i + 1] != '$')
		{
			replace_at(line, i + 1, script);
		}
		else if ((*line)[i] == '$')
		{
			script->errnb = E_UNKNOWN_VAR;
			error_handler(script);
		}
		i++;
	}
}
