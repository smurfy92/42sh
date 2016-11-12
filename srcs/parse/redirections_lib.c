/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:24:49 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 17:26:44 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int			check_rights(t_parse *parse, char **file)
{
	if (access(*file, F_OK) < 0 || access(*file, R_OK) < 0)
	{
		if (access(*file, F_OK) < 0)
			ft_putstr_fd("42sh: no such file or directory: ",2);
		else if (access(*file, R_OK) < 0)
			ft_putstr_fd("42sh: permission denied: ",2);
		ft_putendl_fd(*file, 2);
		parse->fail = 1;
		REMOVE(file);
		return (1);
	}
	return (0);
}