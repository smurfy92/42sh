/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:30:12 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/11 17:00:35 by jtranchi         ###   ########.fr       */
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
	int		ret;

	if (parse->file && (fd = open(parse->file, O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	// faire les redirections;
	if (parse->fd > 0)
		dup2(parse->fd, STDOUT_FILENO);
	ft_dup_redirection(parse);
	ret = is_builtins(parse->cmdsplit);
	if (get_path(parse->cmdsplit[0], grp->root) && ret == 0)
		execve(get_path(parse->cmdsplit[0], grp->root), parse->cmdsplit, NULL);
}

void		ft_fork_pipe(t_group *grp)
{
	int		tabl[2];
	pid_t	pid;
	t_parse	*parse;
	int		fd;
	int ret;

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
		ret = is_builtins(parse->cmdsplit);
		if (get_path(parse->cmdsplit[0], grp->root) && ret == 0)
			execve(get_path(parse->cmdsplit[0], grp->root), parse->cmdsplit, NULL);
		else if (ret == 1)
			builtins(grp);
		exit(0);
	}
	dup2(tabl[0], STDIN_FILENO);
	close(tabl[1]);
}

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
	int 	sig;

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
		exit(0);
	}
	waitpid(grp->father, &sig, 0);
	check_lastcmd(grp);
}

void		andor_exec(t_group *grp)
{
	t_andor *tmp;

	while (grp->allcmd->andor)
	{
		tmp = grp->allcmd->andor;
		REMOVE(&grp->allcmd->andor->cmd);
		pipe_exec(grp);
		grp->allcmd->andor = tmp->next;
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
