/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/10 23:13:07 by julio            ###   ########.fr       */
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

void		ft_dup_redirection(t_parse *parse)
{
	char	**tmp;

	if (parse->redfd)
	{
		tmp = ft_strsplit(parse->redfd, '>');
		parse->fd = dup2(ft_atoi(tmp[0]), ft_atoi(tmp[1]));
		REMOVE(&tmp[0]);
		REMOVE(&tmp[1]);
	}
	if (parse->closefd)
	{
		tmp = ft_strsplit(parse->closefd, ';');
		int i = -1;
		while (tmp[++i])
		{
			close(ft_atoi(tmp[i]));
			REMOVE(&tmp[i]);
		}
		free(tmp);
	}
}

void		exec_child(t_group *grp, t_parse *parse)
{
	int		fd;
	
	if (parse->file && (fd = open(parse->file, O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	// faire les redirections;
	if (parse->fd > 0)
		dup2(parse->fd, STDOUT_FILENO);
	ft_dup_redirection(parse);
	if (get_path(parse->cmdsplit[0], grp->root))
		execve(get_path(parse->cmdsplit[0], grp->root), parse->cmdsplit, NULL);
}

void		ft_fork_pipe(t_group *grp)
{
	int		tabl[2];
	pid_t	pid;
	t_parse	*parse;
	int		fd;

	pipe(tabl);
	parse = grp->allcmd->andor->parselst;
	pid = fork();
	if (pid == 0)
	{
		if (parse->file && (fd = open(parse->file, O_RDONLY)))
			dup2(fd, STDIN_FILENO);
		ft_dup_redirection(parse);
		if (parse->fd > 0)
			dup2(tabl[1], parse->fd);
		else
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
			exec_child(grp, parse);
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
