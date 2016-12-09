/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:21:12 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:29:23 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		assignation_handler(t_assign *assign, t_script *script)
{
	ft_putendl(assign->name);
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

	tmp = ft_strdup(cmd->cmd);
	var_replacer(script, &tmp);
	line = ft_strjoin(tmp, "; ");
	TERM(cmd_line) = ft_strjoin_nf(TERM(cmd_line), line, 1);
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

static int		loop_handler(t_loop *current, t_script *script)
{
	int	ret;

	ret = 1;
	while ((ret = comp_analyzer(current->comp)) == 0)
	{
		action_reader(script, current->acts);
	}
	if (ret > 0)
		error_handler(script);
	return (ret);
}

void			action_reader(t_script *script, t_action *begin)
{
	t_action	*tmp;

	tmp = begin;
	script->fd = (script->fd == 0) ? open("new_script",
		O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU) : script->fd;
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
