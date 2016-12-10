/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:33:45 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/10 06:04:16 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"


static int		get_loop_type(char *line, t_loop *new)
{
	if (ft_strncmp(line, "while ", 6) == 0)
		new->type = LOOP_W;
	else if (ft_strncmp(line, "for ", 4) == 0)
		new->type = LOOP_F;
	else
		return (E_INVALID_LOOP);
	return (0);
}

static t_fold	*get_loop_fold(char *dirname, t_loop *new)
{
	t_fold		*fold;

	fold = (t_fold *)malloc(sizeof(t_fold));
	var_replacer(get_script(NULL), &dirname);
	if (!(fold->dir = opendir(dirname)))
	{
		free(fold);
		return (NULL);
	}
	fold->dirname = ft_strdup(dirname);
	new->f_loop = fold;
	return (fold);
}

static int	prepare_var(t_loop *new, char *varname)
{
	t_assign	*assign;

	assign = new_assignation(varname, "start");
	add_to_list(get_script(NULL), assign);
	assign_free((void **)&assign);
	new->f_loop->tp = ft_strdup(varname);
	return (get_script(NULL)->errnb);
}

static int	folder_checker(char *line, t_loop *new)
{
	char	**clean;
	int		ret;

	clean = ft_strsplit(line, ' ');
	ret = 0;
	if (!clean[0] || !clean[1] || !clean[2] || !clean[3])
		ret = E_INVALID_LOOP;
	else if (ft_strcmp(clean[0], "for") || ft_strcmp(clean[2], "in"))
		ret = E_INVALID_LOOP;
	else if (!(get_loop_fold(clean[3], new)))
		ret = E_INVALID_LOOP_FOLDER;
	else if (prepare_var(new, clean[1]))
		ret = E_INVALID_LOOP;
	ft_freestrtab(&clean);
	return (ret);
}

t_loop		*new_loop(char *text, t_script *script)
{
	int		i;
	char	**clean;
	t_loop	*new;

	i = 0;
	new = (t_loop *)malloc(sizeof(t_loop));
	new->comp = NULL;
	new->f_loop = NULL;
	new->acts = NULL;
	clean = ft_strsplit(text, 135);
	while (clean[i])
	{
		if (i == 0)
		{
			if ((script->errnb = get_loop_type(clean[i], new)))
				error_handler(script);
			if (new->type == LOOP_W)
				script->errnb = get_cond(clean[i], NULL, script, new);
			else if (new->type == LOOP_F)
				script->errnb = folder_checker(clean[i], new);
		}
		if (i == 1 && ft_strcmp(clean[i], "do"))
			return (NULL);
		if (i > 1 && ft_strcmp(clean[i], "done"))
			line_checker(clean, &i, script, &new->acts);
		i++;
	}
	ft_freestrtab(&clean);
	return (new);
}
