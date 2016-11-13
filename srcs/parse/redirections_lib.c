/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:24:49 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 22:14:01 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		ft_del_red_from_cmd(t_parse *parse, int end, int start)
{
	char *tmp;

	while (ft_is_space(parse->cmd[end]) && parse->cmd[end])
		end++;
	tmp = ft_strdup(&parse->cmd[end]);
	parse->cmd[start] = '\0';
	parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
}


char			*get_redirection(t_group *grp, t_parse *parse, int i, int start)
{
	int		end;
	char	*tmp;

	while (parse->cmd[i] && !ft_isalpha(parse->cmd[i]) &&
	!ft_isdigit(parse->cmd[i]) && !ft_is_quote(parse->cmd[i]))
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

int			check_rights(t_parse *parse, char **file, int i)
{
	if (i == 0 && access(*file, F_OK) == 0 && access(*file, W_OK) < 0)
	{
		ft_putstr_fd("42sh: permission denied: ",2);
		ft_putendl_fd(*file, 2);
		parse->fail = 1;
		REMOVE(file);
		return (1);
	}
	else if (i == 1 && (access(*file, F_OK) < 0 || access(*file, R_OK) < 0))
	{
		if (access(*file, F_OK) < 0)
			error_cmd("42sh: no such file or directory: ", *file, 1);
		else if (access(*file, R_OK) < 0)
			error_cmd("42sh: permission denied: ", *file, 1);
		//to check if that's a file
		parse->fail = 1;
		REMOVE(file);
		return (1);
	}
	return (0);
}

void		ft_redirection_error(t_parse *parse, int end)
{
	char *tmp;

	tmp = ft_strjoin_nf(ft_strjoin("42sh : parse error near `",
	&parse->cmd[end - 1]), "'", 1);
	ft_putendl_fd(tmp, 2);
	ft_strdel(&tmp);
}