/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:40:40 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/13 01:49:43 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	init le centre de la liste
*/

t_comp		*rtcomp_init(int start, char *val)
{
	t_comp		*begin;

	begin = (t_comp *)malloc(sizeof(t_comp));
	begin->val = ft_strdup(val);
	begin->c_type = 0;
	begin->start = start;
	begin->next = begin;
	begin->prev = begin;

	return (begin);

}


/*
**	free la liste comp a chaque fois quun autre char que TAB est tape
*/

void		comp_free(t_group *grp, t_comp **begin)
{
	t_comp	*tmp;
	t_comp	*tmp2;

	tmp = (*begin)->next;
	grp->comp->c_type = 0;
	grp->comp->start = 0;
	while (tmp != (*begin))
	{
		ft_strdel(&tmp->val);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	ft_strdel(&tmp->val);
	free(*begin);
	*begin = NULL;
	display_next(grp, 1);
}

/*
**	initialise la compleion selon cmd/path ou la display seulement si elle est initialisee
*/

void		comp_init(t_group *grp, t_comp **comp)
{
	char	*tmp;

	tmp = NULL;
	if (TERM(curs_pos) != TERM(cmd_size))
		return ;
	if (grp->comp != NULL)
		return (display_next(grp, 0));
	else if (TERM(cmd_line) == NULL || ft_strcmp(TERM(cmd_line), "") == 0)
		return ;
	else if (!ft_strchr(TERM(cmd_line), '/') && ft_strcmp(get_last_word(TERM(cmd_line)), TERM(cmd_line)) == 0)
		cmd_finder(grp, comp);
	else if (ft_strcmp(get_last_word(TERM(cmd_line)), " ") == 0 ||
		(ft_strlen(get_last_word(TERM(cmd_line))) > 1 && !ft_strchr(get_last_word(TERM(cmd_line)), '/')))
		file_finder(grp, ".", comp);
	else if (ft_strchr(get_last_word(TERM(cmd_line)), '/'))
		file_finder(grp, (tmp = get_dirtop(TERM(cmd_line))), comp);
	if (grp->comp && grp->comp->c_type > 0)
		display_next(grp, 0);
	if (grp->comp && grp->comp->c_type == 1)
		comp_free(grp, &grp->comp);
	if (tmp)
		ft_strdel(&tmp);
}