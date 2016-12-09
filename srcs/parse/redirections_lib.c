/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:24:49 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/23 23:02:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** removing parsed redirection from parse cmd
*/

static void		ft_del_red_from_cmd(t_parse *parse, int end, int start)
{
	char *tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
}

/*
** returning redirection file if found
** else returning null and printing error
*/

char			*get_redirection(t_group *grp, t_parse *parse, int i, int start)
{
	int		end;
	char	*tmp;

	if (grp)
	{}
	while (parse->cmd[i] && parse->cmd[i] == ' ')
		i++;
	end = i;
	while (parse->cmd[end] && !ft_end_of_red(parse->cmd[end]))
		end++;
	if (end == i && (grp->fail = 1))
	{
		ft_redirection_error(parse, end);
		return (NULL);
	}
	tmp = ft_strsub(&parse->cmd[i], 0, end - i);
	ft_del_red_from_cmd(parse, end, start);
	return (tmp);
}

/*
** check if redirection file is not a directory
** printing error if it is a directory
*/

int				check_stat(t_parse *parse, char **file)
{
	struct stat		buf;
	char			*tmp;

	tmp = NULL;
	tmp = getwd(tmp);
	tmp = ft_strjoin_nf(tmp, "/", 1);
	tmp = ft_strjoin_nf(tmp, *file, 1);
	stat(tmp, &buf);
	REMOVE(&tmp);
	if (S_ISDIR(buf.st_mode))
	{
		error_cmd("is a directory: ", *file, 1);
		REMOVE(file);
		parse->fail = 1;
		return (1);
	}
	return (0);
}

/*
** checking rights on rediretions files
** printing error if rights are not ok
*/

int				check_rights(t_parse *parse, char **file, int i)
{
	if (i == 0 && access(*file, F_OK) == 0 && access(*file, W_OK) < 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(*file, 2);
		parse->fail = 1;
		REMOVE(file);
		return (1);
	}
	else if (i == 1 && (access(*file, F_OK) < 0 || access(*file, R_OK) < 0))
	{
		if (access(*file, F_OK) < 0)
			error_cmd("no such file or directory: ", *file, 1);
		else if (access(*file, R_OK) < 0)
			error_cmd("permission denied: ", *file, 1);
		parse->fail = 1;
		REMOVE(file);
		return (1);
	}
	if (check_stat(parse, file))
		return (1);
	return (0);
}

/*
** printing error if wrong parse format
*/

void			ft_redirection_error(t_parse *parse, int end)
{
	char *tmp;

	parse->cmd[end] = '\0';
	tmp = ft_strjoin_nf(ft_strjoin("`",
	&parse->cmd[end - 1]), "'", 1);
	error_cmd("parse error near ", tmp, 1);
	ft_strdel(&tmp);
}
