/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:15:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/14 19:29:46 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		is_fg(t_jobs *pgid, int fg)
{
	t_jobs	*pipe;

	pipe = pgid;
	while (pipe)
	{
		pipe->fg = fg;
		pipe = pipe->next_pipe;
	}
}

void		launch_exec(t_group *grp, t_parse *parse, char *andorcmd, int fg)
{
	t_parse	*tmp;
	t_jobs	*parent;
	int		is_built;

	tmp = parse;
	parent = NULL;
	is_built = false;
	grp->pipefd_in = STDIN_FILENO;
	while (tmp)
	{
		is_built = is_builtins(tmp->cmdsplit);
		if (!tmp->fail && (!fg || !is_built || tmp->next || tmp->fd > -1))
			generate_process(&parent, tmp, andorcmd, fg);
		else if (is_built && tmp->fd < 0)
			generate_builtin(&parent, tmp, andorcmd, fg);
		is_fg(parent, fg);
		tmp = tmp->next;
	}
	parent && !fg ? display_jobs(parent, 1, 1) : 0;
	if (grp->is_interact == false)
		waitpid(grp->father, NULL, WUNTRACED);
	else if (fg && parent)
		put_in_fg(grp, parent);
	else if (parent)
		sleep(1);
}

int			create_fd(t_parse *parse)
{
	t_parse		*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp->file && check_rights(tmp, &tmp->file, 1))
			return (0);
		if (tmp->sgred && check_rights(tmp, &tmp->sgred, 0))
			return (0);
		if (tmp->dbred && check_rights(tmp, &tmp->dbred, 0))
			return (0);
		if (tmp->sgred || tmp->dbred)
		{
			(parse->fd != -1) ? close(parse->fd) : 0;
			ft_create_redirections(tmp);
		}
		tmp = tmp->next;
	}
	return (1);
}

void		andor_exec(t_group *grp, t_andor *andor)
{
	t_andor *tmp;

	tmp = andor;
	while (tmp)
	{
		if (create_fd(tmp->parselst))
			launch_exec(grp, tmp->parselst, tmp->cmd, (tmp->type == 3) ? 0 : 1);
		if (grp && tmp && ((tmp->type == 1 && grp->exit != 0) ||
					(tmp->type == 2 && grp->exit == 0)))
			break ;
		if (tmp->next)
			grp->exit = 0;
		tmp = tmp->next;
	}
}

void		init_exec(t_group *grp)
{
	t_allcmd *tmp;

	tmp = grp->allcmd;
	if (!grp->fail)
	{
		while (tmp)
		{
			grp->exit = 0;
			andor_exec(grp, tmp->andor);
			tmp = tmp->next;
		}
	}
	free_allcmd(grp);
}
