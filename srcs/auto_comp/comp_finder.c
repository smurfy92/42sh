/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 01:45:04 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/18 17:32:59 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	cherche toutes les possibilites et remplis une list comp
**	pour les commandes
*/

void		cmd_finder(t_group *grp, t_comp **comp)
{
	char	**result;
	char	*tmp;
	int		i;
	t_hash	*start;

	i = -1;
	if (!grp->root)
		return ;
	start = get_startnode(TERM(cmd_line), grp->root);
	if (start == NULL)
		return ;
	tmp = get_possible(start, ft_strlen(grp->root->charlist), 1);
	if (tmp == NULL)
		return ;
	result = ft_strsplit(tmp, ' ');
	*comp = rtcomp_init(ft_strlen(TERM(cmd_line)), TERM(cmd_line));
	(*comp)->type = C_COM;
	while (result[++i])
	{
		grp->comp->c_type++;
		new_comp(result[i], &grp->comp, C_COM, grp->comp->start);
	}
	ft_freestrtab(&result);
}

/*
**	effectue derniers checks sur lajout a la liste et ajoute si OK
*/

void		create_comp(struct dirent *cur_e, char *lw, t_group *grp)
{
	if (ft_strcmp(cur_e->d_name, ".") != 0 &&
		ft_strcmp(cur_e->d_name, "..") != 0)
	{
		if ((lw[1] == '.') ? cur_e->d_name[0] == '.' :
			cur_e->d_name[0] != '.')
		{
			grp->comp->c_type++;
			new_comp(cur_e->d_name, &grp->comp,
				CIS_D(cur_e->d_type), ft_strlen(lw) - 1);
		}
	}
}

/*
**	ouvre un dossier donne en parametre et compare son contenu avec last
**	word pour afficher les posssibles
*/

int			file_finder(t_group *grp, char *dir, t_comp **comp)
{
	DIR				*o_dir;
	struct dirent	*cur_e;
	char			*lw;

	lw = get_last_word(TERM(cmd_line));
	point_onlast(&lw);
	if (!(o_dir = opendir(dir)))
		return (1);
	*comp = rtcomp_init(ft_strlen(TERM(cmd_line)), TERM(cmd_line));
	while ((cur_e = readdir(o_dir)))
	{
		if (ft_strlen(lw) <= 1 ||
			ft_strncmp(cur_e->d_name, lw + 1, ft_strlen(lw) - 1) == 0)
			create_comp(cur_e, lw, grp);
	}
	closedir(o_dir);
	return (0);
}
