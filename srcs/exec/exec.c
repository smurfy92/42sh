/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/05 17:06:34 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		exec(t_group *grp)
{
	int	ret;

	ret = builtins(grp);
	ret == -1 ? printf("ERROR IN BUILTINS\n") : 0;
	if (ret == 0)
	{
		// if (get_path(grp->parselst->cmdsplit[0], grp->root))
		// {
		// 	//execve(get_path(grp->parselst->cmdsplit[0], grp->root), grp->parselst->cmdsplit, NULL);
		// }
	}
}

void		ft_fork_pipe(t_group *grp)
{
	int		tabl[2];
	pid_t pid;
	t_parse *parse;

	pipe(tabl);

	parse = grp->allcmd->andor->parselst;
	pid = fork();
	if (pid == 0)
	{
		dup2(tabl[1], STDOUT_FILENO);
		close(tabl[0]);
		if (get_path(parse->cmdsplit[0], grp->root))
			execve(get_path(parse->cmdsplit[0], grp->root), parse->cmdsplit, NULL);
		exit(0);
	}
	dup2(tabl[0], STDIN_FILENO);
	close(tabl[1]);
}

void		pipe_exec(t_group *grp)
{
	t_parse *tmp3;
	t_parse *parse;

	while (grp->allcmd->andor->parselst)
	{
		parse = grp->allcmd->andor->parselst;
		if (parse->next)
			ft_fork_pipe(grp);
		else
		{
			if (get_path(parse->cmdsplit[0], grp->root))
				execve(get_path(parse->cmdsplit[0], grp->root), parse->cmdsplit, NULL);
		}
		tmp3 = parse;
		grp->allcmd->andor->parselst = tmp3->next;
		free_parselst(tmp3);
	}
}

void		andor_exec(t_group *grp)
{
	t_andor *tmp2;

	//si un executable
	pid_t pid = fork();
	if (pid == 0)
	{
		while (grp->allcmd->andor)
		{
			tmp2 = grp->allcmd->andor;
			REMOVE(&grp->allcmd->andor->cmd);
			pipe_exec(grp);
			grp->allcmd->andor = tmp2->next;
			free(tmp2);
		}
		//tmp exit
		exit(0);
	}
	wait(0);
}

void		init_exec(t_group *grp)
{
	t_allcmd *tabl;

	while (grp->allcmd)
	{
		tabl = grp->allcmd;
		REMOVE(&tabl->cmd);
		andor_exec(grp);
		grp->allcmd = tabl->next;
		free(tabl);
		tabl = grp->allcmd;
	}
}
