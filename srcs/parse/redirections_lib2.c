/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_lib2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:58:55 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/10 06:10:29 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** parsing for '<'
** format char*
** replacing if existed
*/

void		ft_addfile(t_group *grp, t_parse *parse, int i)
{
	if (parse->file)
		REMOVE(&parse->file);
	parse->file = get_redirection(grp, parse, i, i - 1);
}

/*
** parsing for '>>'
** format char*
** replacing if existed
*/

void		ft_adddoubleredirection(t_group *grp, t_parse *parse, int i)
{
	if (parse->dbred)
		REMOVE(&parse->dbred);
	if (parse->sgred)
		REMOVE(&parse->sgred);
	parse->dbred = get_redirection(grp, parse, i, i - 2);
}

/*
** parsing for '>'
** format char*
** replacing if existed
*/

void		ft_addredirection(t_group *grp, t_parse *parse, int i)
{
	if (parse->sgred)
		REMOVE(&parse->sgred);
	if (parse->dbred)
		REMOVE(&parse->dbred);
	parse->sgred = get_redirection(grp, parse, i, i - 1);
}
