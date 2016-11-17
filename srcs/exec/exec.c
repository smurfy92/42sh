/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 17:49:16 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		check_lastcmd(t_group *grp, t_parse *parse)
{
	t_parse *tmp;

	tmp = parse;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (is_builtins(tmp->cmdsplit))
		builtins(grp, tmp);
}

void		pipe_exec(t_group *grp, t_parse *parse)
{
	t_parse *tmp;
	int			ret;

	tmp = parse;
	grp->father = fork();
	if (grp->father == 0)
	{
		while (tmp)
		{
			if (!tmp->fail)
			{
				if (tmp->next)
					ft_fork_pipe(grp, tmp);
				else
					exec_child(grp, tmp);
			}
			tmp = tmp->next;
		}
		ft_exit(grp, EXIT_FAILURE);
	}
	waitpid(grp->father, &ret, 0);
	error_process_check(ret);
	check_lastcmd(grp, tmp);
	if (ret > 0)
		grp->exit = 1;
}

void		andor_exec(t_group *grp, t_andor *andor)
{
	t_andor *tmp;

	tmp = andor;
	while (tmp)
	{
		reset_shell();
		pipe_exec(grp, tmp->parselst);
		init_shell();
		if ((tmp->type == 1 && grp->exit != 0) ||
			(tmp->type == 2 && grp->exit == 0))
		{
			grp->exit = 0;
			break ;
		}
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
			andor_exec(grp, tmp->andor);
			tmp = tmp->next;
		}
	}
	free_allcmd(grp);
	grp->fail = 0;
}
