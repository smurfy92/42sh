/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:15:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/01 05:07:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		check_lastcmd(t_group *grp, t_parse *parse, t_jobs *jobs, int fg)
{
	t_parse		*tmp;
	int			ret;
	int			is_built;

	tmp = parse;
	while (tmp && tmp->next)
		tmp = tmp->next;
	is_built = is_builtins(tmp->cmdsplit);
	if ((!is_built || !fg) && grp->is_interact)
	{
		jobs = create_jobs(grp, parse->cmd, grp->father);
		setpgid (grp->father, grp->father);
	}
	if (is_built && parse->fd < 0)
	{
		waitpid(grp->father, &ret, 0);
		builtins(grp, tmp);
	}
	else if (grp->is_interact == false)
		waitpid(grp->father, &ret, 0);
	else if (fg)
		put_in_fg(grp, jobs);
}

void		launch_exec(t_group *grp, t_parse *parse, t_jobs *jobs, int fg)
{
	t_parse		*tmp;

	tmp = parse;
	grp->father = fork();
	grp->father < 0 ? ft_exit(grp, 999) : 0;
	if (grp->father == 0)
	{
		if (!is_builtins(tmp->cmdsplit))
			init_shell_job(grp->father, fg);
		while (tmp)
		{
			if (!tmp->fail)
				(tmp->next && tmp->fd == -1) ? ft_fork_pipe(grp, tmp) :
					exec_child(0, grp, tmp);
			tmp = tmp->next;
		}
		ft_exit(grp, EXIT_FAILURE);
	}
	else
		check_lastcmd(grp, tmp, jobs, fg);
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
		launch_exec(grp, tmp->parselst, NULL, (tmp->type == 3) ? 0 : 1);
		restore_shell();
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
			andor_exec(grp, tmp->andor);
			tmp = tmp->next;
		}
	}
	free_allcmd(grp);
	grp->fail = 0;
}
