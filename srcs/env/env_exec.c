/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:48:03 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/12 08:11:14 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	ret = is_builtins(cmd_split);
**	ici cest les binaire qui sont exec pas les builtins
**	to check if we need to exec builtin
*/

void	exec_builtins(t_group *grp, t_parse *parse)
{
	ENV(fg) = 0;
	ENV(pgid) = NULL;
	free_env_tmp(grp);
	builtins(grp, parse);
}

static void		exec_env(t_group *grp, t_parse *parse)
{
	int		ret;
	char	*path;
	char	**env;

	dup2(grp->pipefd_in, STDIN_FILENO);
	if (ENV(path_tmp) != NULL)
	{
		root_hfree(&grp->root);
		hash_init(&grp->root, grp, ENV(path_tmp));
	}
	ret = is_builtins(parse->cmdsplit);
	path = get_path(parse->cmdsplit[0], grp->root);
	if (ret == 0 && check_cmd(&path, parse->cmdsplit[0]) == 0 && path)
	{
		env = list_to_tab(ENV(lst));
		execve(path, parse->cmdsplit, env);
		ft_freestrtab(&env);
	}
	else if (ret == 0)
		ft_exit(grp, EXIT_FAILURE);
	else if (ret == 1)
		exec_builtins(grp, parse);
	ft_exit(grp, grp->exit);
}

void		init_exec_env(t_group *grp)
{
	t_parse	*parse;

	parse = (t_parse*)malloc(sizeof(t_parse));
	parse->cmd = ft_strtrim(ENV(cmd));
	parse->cmdsplit = ft_spacesplit(ENV(cmd));
	parse->heredoc = 0;
	parse->errnb = 0;
	parse->fd = -1;
	parse->fail = 0;
	parse->dbred = NULL;
	parse->sgred = NULL;
	parse->file = NULL;
	parse->redfd = NULL;
	parse->closefd = NULL;
	parse->bquotes = NULL;
	parse->next = NULL;
	if (grp->father != 0)
	{
		grp->father = fork();
		grp->father == -1 ? exit(999) : 0;
		if (grp->father == 0)
			init_shell_job(ENV(pgid) ? ENV(pgid)->pid : 0, ENV(fg));
	}
	if (grp->father == 0)
		exec_env(grp, parse);
}
