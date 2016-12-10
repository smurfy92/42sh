/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:21:12 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/10 05:02:39 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		assignation_handler(t_assign *assign, t_script *script)
{
	add_to_list(script, assign);
	if (script->errnb)
		error_handler(script);
}

/*
**	classiic line
*/

static void		line_handler(t_line *cmd, t_script *script, t_group *grp)
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
	// write(script->fd, line, ft_strlen(line));
	ft_strdel(&line);
	ft_strdel(&tmp);
}

static void		condition_handler(t_cond *curr, t_script *script)
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

static int		run_loop_dir(t_loop *current, t_script *script)
{
	struct dirent	*cur_e;
	// char			buff[512];
	char			*name;
	t_assign		*new_a;

	if (!current->f_loop)
		return (E_INVALID_LOOP_FOLDER);
	while ((cur_e = readdir(current->f_loop->dir)))
	{
		if (cur_e->d_name[0] != '.')
		{
			name = ft_strjoin_nf(ft_strjoin(current->f_loop->dirname, "/"), cur_e->d_name, 1);
			// ft_putendl(name);
			new_a = new_assignation(current->f_loop->tp, name);
			ft_putendl(new_a->value);
			add_to_list(script, new_a);
			action_reader(script, current->acts);
			assign_free((void **)&new_a);
			ft_strdel(&name);
		}
	}
	closedir(current->f_loop->dir);
	current->f_loop = NULL;
	return (0);
}

static int		loop_handler(t_loop *current, t_script *script)
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
	{
		run_loop_dir(current, script);
	}
	return (ret);
}

void			action_reader(t_script *script, t_action *begin)
{
	t_action	*tmp;

	tmp = begin;
	// script->fd = (script->fd == 0) ? open("new_script",
	// 	O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU) : script->fd;
	while (tmp)
	{
		if (tmp->type == ASSIGN_T)
			assignation_handler((t_assign *)tmp->action, script);
		else if (tmp->type == LINE_T)
			line_handler(tmp->action, script, get_grp());
		else if (tmp->type == COND_T)
			condition_handler(tmp->action, script);
		else if (tmp->type == LOOP_T)
			loop_handler(tmp->action, script);
		tmp = tmp->next;
	}
}
