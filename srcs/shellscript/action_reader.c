/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:21:12 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 16:57:54 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		assignation_handler(t_assign *assign, t_script *script)
{
	add_to_list(script, assign);
	if (script->errnb)
		error_handler(script);
}

/*
**	classiic line
*/

void		line_handler(t_line *cmd, t_script *script, t_group *grp)
{
	char	*line;
	char	*tmp;

	if (grp)
		;
	tmp = ft_strdup(cmd->cmd);
	var_replacer(script, &tmp);
	line = ft_strjoin(tmp, "; ");
	TERM(cmd_line) = ft_strjoin_nf(TERM(cmd_line), line, 1);
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_strdel(&line);
	ft_strdel(&tmp);
}

void		condition_handler(t_cond *curr, t_script *script)
{
	t_cond		*tmp;
	int			success;

	tmp = curr;
	success = -1;
	while (tmp)
	{
		if (tmp->type == COND_FI)
			break ;
		if (success == 0)
			break ;
		success = perform_condition(tmp, script);
		tmp = tmp->next;
	}
}

int			run_loop_dir(t_loop *current, t_script *script)
{
	struct dirent	*cur_e;
	char			*name;
	t_assign		*new_a;

	if (!current->f_loop)
		return (E_INVALID_LOOP_FOLDER);
	while ((cur_e = readdir(current->f_loop->dir)))
	{
		if (cur_e->d_name[0] != '.')
		{
			name = ft_strjoin_nf(ft_strjoin(current->f_loop->dirname, "/"),
				cur_e->d_name, 1);
			new_a = new_assignation(current->f_loop->tp, name);
			add_to_list(script, new_a);
			action_reader(script, current->acts);
			assign_free((void **)&new_a);
			ft_strdel(&name);
		}
	}
	closedir(current->f_loop->dir);
	current->f_loop->dir = NULL;
	return (0);
}

int			loop_handler(t_loop *current, t_script *script)
{
	int	ret;

	ret = 1;
	if (current->type == LOOP_W)
	{
		while ((ret = comp_analyzer(current->comp)) == 0)
		{
			action_reader(script, current->acts);
		}
		if (ret > 0)
			error_handler(script);
	}
	else if (current->type == LOOP_F)
		run_loop_dir(current, script);
	return (ret);
}
