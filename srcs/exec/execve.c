/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 02:28:21 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/12 03:44:34 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		check_cmd(char **path, char *cmd)
{
	struct stat	s_buf;
	mode_t		val;
	int			ret;

	if (*path == NULL)
		*path = SDUP(cmd);
	ret = lstat(*path, &s_buf);
	val = (s_buf.st_mode & ~S_IFMT);
	if (ret != 0)
		error_cmd("unknown command", cmd, 1);
	else if (s_buf.st_size <= 0)
		error_cmd("executable format error", cmd, 1);
	else if (!(val & S_IXUSR) || S_ISDIR(s_buf.st_mode))
		error_cmd("Permission denied", cmd, 1);
	else
		return (0);
	return (-1);
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
	char	*path;

	if (parse->file && (fd = open(parse->file, O_RDONLY)))
		dup2(fd, STDIN_FILENO);
	if (parse->fd > 0)
		dup2(parse->fd, STDOUT_FILENO);
	ft_dup_redirection(parse);
	ret = is_builtins(parse->cmdsplit);
	path = get_path(parse->cmdsplit[0], grp->root);
	if (ret == 0 && check_cmd(&path, parse->cmdsplit[0]) == 0 && path)
		execve(path, parse->cmdsplit, NULL); // add ENV char **
	else if (ret == 0)
		exit(EXIT_FAILURE);
	exit(0);
}

void		ft_fork_pipe(t_group *grp)
{
	int		tabl[2];
	pid_t	pid;
	t_parse	*parse;
	int		fd;
	int 	ret;
	char	*path;

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
		path = get_path(parse->cmdsplit[0], grp->root);
		if (ret == 0 && check_cmd(&path, parse->cmdsplit[0]) == 0 && path)
			execve(path, parse->cmdsplit, NULL); // add ENV char **
		else if (ret == 1)
			builtins(grp);
		else
			exit(EXIT_FAILURE);
		exit(grp->exit);
	}
	dup2(tabl[0], STDIN_FILENO);
	close(tabl[1]);
}