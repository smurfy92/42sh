/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 03:30:46 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		check_lastcmd(t_group *grp)
{
	t_parse *tmp;

	tmp = grp->allcmd->andor->parselst;
	while (tmp->next)
		tmp = tmp->next;
	if (is_builtins(tmp->cmdsplit))
	{
		CMD(cmdsplit) = tmp->cmdsplit;
		builtins(grp);
	}
}

void		pipe_exec(t_group *grp)
{
	t_parse *tmp;
	int			ret;
	grp->father = fork();
	if (grp->father == 0)
	{
		while (grp->allcmd->andor->parselst)
		{
			tmp = grp->allcmd->andor->parselst;
			if (tmp->next)
				ft_fork_pipe(grp);
			else
				exec_child(grp, tmp);
			grp->allcmd->andor->parselst = tmp->next;
			free_parselst(tmp);
		}
		exit(EXIT_FAILURE);
	}
	waitpid(grp->father, &ret, 0);
	check_lastcmd(grp);
	if (ret > 0)
		grp->exit = 1;
}

void		andor_exec(t_group *grp)
{
	t_andor *tmp;
	int 	ret;

	ret = 0;
	while (grp->allcmd->andor)
	{
		tmp = grp->allcmd->andor;
		REMOVE(&grp->allcmd->andor->cmd);
		pipe_exec(grp);
		if ((tmp->type == 1 && grp->exit != 0) ||
			(tmp->type == 2 && grp->exit == 0))
		{
			free(tmp);
			grp->exit = 0;
			break ;
		}
		grp->allcmd->andor = tmp->next;
		grp->exit = 0;
		free(tmp);
	}
}

void		init_exec(t_group *grp)
{
	t_allcmd *tmp;

	while (grp->allcmd)
	{
		tmp = grp->allcmd;
		REMOVE(&tmp->cmd);
		andor_exec(grp);
		grp->allcmd = tmp->next;
		free(tmp);
		tmp = grp->allcmd;
	}
}
