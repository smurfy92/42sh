/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 01:39:57 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/18 17:55:45 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	return le dernier mot de cmd
*/

char		*get_last_word(char *cmd)
{
	return ((!ft_strrchr(cmd, ' ')) ? cmd : ft_strrchr(cmd, ' '));
}

/*
**	retourne le dernier dossier dans une str avec '/'
*/

void		point_onlast(char **lw)
{
	if (ft_strchr(*lw, '/'))
		*lw = ft_strrchr(*lw, '/');
}

/*
**	retourne le directory a ouvrir pour file_finder
*/

char		*get_dirtop(char *cmd)
{
	int		stop;
	char	*tmp;

	if (cmd[0] == '/' && ft_strcmp(get_last_word(cmd), cmd) == 0 &&
		(ft_strchr(cmd, '/') == ft_strrchr(cmd, '/')))
	{
		tmp = ft_strdup("/");
		return (tmp);
	}
	stop = ft_strlen(ft_strrchr(cmd, '/'));
	tmp = ft_strsub(get_last_word(cmd),
		(ft_strcmp(get_last_word(cmd), cmd) == 0) ? 0 : 1,
		ft_strlen(get_last_word(cmd)) - stop);
	return (tmp);
}

/*
**	verifie la validite du pointeur actuel dans la liste comp
*/

void		update_name(t_group *grp, char **name, t_comp **last, int comp_free)
{
	if (comp_free != 0)
	{
		if (*name)
			ft_strdel(name);
		*name = NULL;
		*last = NULL;
		return ;
	}
	if (*name == NULL || ft_strcmp(*name, grp->comp->val) != 0)
	{
		if (*name)
			ft_strdel(name);
		(*name) = ft_strdup(grp->comp->val);
		(*last) = grp->comp;
	}
}
