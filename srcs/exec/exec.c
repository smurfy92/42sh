/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:15:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/27 01:07:50 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		check_lastcmd(t_group *grp, t_parse *parse)
{
	t_parse *tmp;

	tmp = parse;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (is_builtins(tmp->cmdsplit) && parse->fd < 0)
		builtins(grp, tmp);
}

void		pipe_exec(t_group *grp, t_parse *parse)
{
	t_parse		*tmp;
	int			ret;

	tmp = parse;
	grp->father = fork();
	grp->father < 0 ? ft_exit(grp, 999) : 0;
	grp->program_pid = grp->father;
	if (grp->father == 0)
	{
		while (tmp)
		{
			if (!tmp->fail)
				(tmp->next && tmp->fd == -1) ? ft_fork_pipe(grp, tmp) :
					exec_child(0, grp, tmp);
			tmp = tmp->next;
		}
		ft_exit(grp, EXIT_FAILURE);
	}
	waitpid(grp->father, &ret, 0);
	grp->program_pid = getpid();
	error_process_check(ret);
	grp->exit = (ret > 0 ? 1 : 0);
	check_lastcmd(grp, tmp);
}

void		create_fd(t_parse *parse)
{
	t_parse		*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp->sgred || tmp->dbred)
			ft_create_redirections(tmp);
		tmp = tmp->next;
	}
}

void		andor_exec(t_group *grp, t_andor *andor)
{
	t_andor *tmp;

	tmp = andor;
	while (tmp)
	{
		reset_shell();
		create_fd(tmp->parselst);
		tmp->type == 3 ? init_job_control(grp, tmp) : pipe_exec(grp, tmp->parselst);
		init_shell();
		if ((tmp->type == 1 && grp->exit != 0) ||
			(tmp->type == 2 && grp->exit == 0))
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
		grp->exit = 0;
		while (tmp)
		{
			if (!check_redirections_rights(tmp->andor))
				break;
			andor_exec(grp, tmp->andor);
			tmp = tmp->next;
		}
	}
	free_allcmd(grp);
	grp->fail = 0;
}
