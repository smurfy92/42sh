/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:57:34 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:09:35 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	singletone
*/

t_script	*get_script(t_script *script)
{
	static t_script		*stat;

	if (script)
		stat = script;
	return (stat);
}

/*
**	creee un nouveau t_script au de debut de linterpet
*/

t_script	*new_script(void)
{
	t_script	*new;

	new = (t_script *)malloc(sizeof(t_script));
	new->begin = NULL;
	new->rd_fd = 0;
	new->fd = 0;
	new->errno = 0;
	new->vars = NULL;
	get_script(new);
	return (new);
}
