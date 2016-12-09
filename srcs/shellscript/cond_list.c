/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:02:20 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 06:07:54 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		help_to_free(char ***tmp, char ***clean)
{
	if (tmp)
		ft_freestrtab(tmp);
	if (clean)
		ft_freestrtab(clean);
}

/*
**	splite la chaine pour avoir uniquemment le necessaire a envoyer a com_list,
**	verifie ausssi la validite de la condi
*/

int				get_cond(char *line, t_cond *cond,
	t_script *script, t_loop *loop)
{
	char		**clean;
	char		**tmp;

	if (!ft_strchr(line, '[') || !ft_strchr(line, ']'))
		return (E_INCOMPLETE_COND);
	tmp = ft_strsplit(line, '[');
	if (!tmp[1])
	{
		help_to_free(&tmp, NULL);
		return (E_INCOMPLETE_COND);
	}
	clean = ft_strsplit(tmp[1], ']');
	if (ft_strncmp(tmp[1], clean[0], ft_strlen(tmp[1]) - 1) ||
		ft_strlen(clean[1]))
	{
		help_to_free(&tmp, &clean);
		return (E_INCOMPLETE_COND);
	}
	if (cond)
		cond->comp = new_comparaison(clean[0], script);
	if (loop)
		loop->comp = new_comparaison(clean[0], script);
	help_to_free(&clean, &tmp);
	return (0);
}

static int		cond_parser(t_cond *cond, t_script *script)
{
	char	**full_c;
	int		i;

	i = 0;
	full_c = ft_strsplit(cond->text, 135);
	if (cond->type == COND_FI)
	{
		ft_freestrtab(&full_c);
		return (0);
	}
	while (full_c[i])
	{
		if (i == 0 && ft_strncmp(full_c[i], "fi", 2))
			script->errnb = get_cond(full_c[i], cond, script, NULL);
		else if (i == 1 && ft_strcmp(full_c[i], "then"))
			script->errnb = E_INCOMPLETE_COND;
		else if (i > 1)
			line_checker(full_c, &i, script, &cond->acts);
		i++;
	}
	ft_freestrtab(&full_c);
	return (0);
}

t_cond			*new_cond(char *text, t_script *script, t_cond **begin)
{
	t_cond		*new;
	t_cond		*tmp;

	tmp = *begin;
	new = (t_cond *)malloc(sizeof(t_cond));
	new->comp = NULL;
	new->next = NULL;
	new->acts = NULL;
	new->text = ft_strdup(text);
	if (ft_strncmp(text, "fi", 2) == 0)
		new->type = COND_FI;
	else if (ft_strncmp(text, "if ", 3) == 0)
		new->type = COND_IF;
	else if (ft_strncmp(text, "elif ", 5) == 0)
		new->type = COND_ELIF;
	else if (ft_strncmp(text, "else", 4) == 0)
		new->type = COND_ELSE;
	script->errnb = cond_parser(new, script);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*begin = new;
	return (new);
}
