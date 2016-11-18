/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 01:38:59 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/18 17:54:59 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void	first_display(t_comp **last, t_group *grp, char *name)
{
	char	*tmp2;

	(*last) = ((*last)->next == grp->comp) ? (*last)->next->next :
		(*last)->next;
	remove_line(grp);
	tmp2 = ft_strsub((*last)->val, grp->comp->start,
		ft_strlen((*last)->val) - grp->comp->start);
	TERM(cmd_line) = ft_strjoin(name, tmp2);
	TERM(curs_pos) = ft_strlen(TERM(cmd_line));
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_putstr_fd(TERM(cmd_line), 2);
	ft_strdel(&tmp2);
}

static void	second_display(t_comp **last, t_group *grp, char *name)
{
	char	*tmp;
	char	*tmp2;

	(*last) = ((*last)->next == grp->comp) ? (*last)->next->next :
		(*last)->next;
	remove_line(grp);
	tmp2 = ft_strsub((*last)->val, grp->comp->start,
		ft_strlen((*last)->val) - grp->comp->start);
	tmp = ft_strjoin(name, tmp2);
	TERM(cmd_line) = ft_strjoin(tmp, " ");
	TERM(curs_pos) = ft_strlen(TERM(cmd_line));
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_putstr_fd(TERM(cmd_line), 2);
	ft_strdel(&tmp2);
	ft_strdel(&tmp);
}

static void	third_display(t_comp **last, t_group *grp)
{
	char	*tmp;
	char	*tmp2;

	(*last) = ((*last)->next == grp->comp) ? (*last)->next->next :
		(*last)->next;
	tmp = ft_strsub((*last)->val, (*last)->start,
		ft_strlen((*last)->val) - (*last)->start);
	remove_line(grp);
	tmp2 = ft_strjoin(grp->comp->val, tmp);
	TERM(cmd_line) = ((*last)->c_type == 1) ? ft_strjoin(tmp2, "/") :
		ft_strdup(tmp2);
	TERM(curs_pos) = ft_strlen(TERM(cmd_line));
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_putstr_fd(TERM(cmd_line), 2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

static void	fourth_display(t_comp **last, t_group *grp)
{
	char	*tmp;
	char	*tmp2;

	(*last) = ((*last)->next == grp->comp) ? (*last)->next->next :
		(*last)->next;
	tmp = ft_strsub((*last)->val, (*last)->start,
		ft_strlen((*last)->val) - (*last)->start);
	remove_line(grp);
	tmp2 = ft_strjoin(grp->comp->val, tmp);
	TERM(cmd_line) = ((*last)->c_type == 1) ? ft_strjoin(tmp2, "/") :
		ft_strjoin(tmp2, " ");
	TERM(curs_pos) = ft_strlen(TERM(cmd_line));
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_putstr_fd(TERM(cmd_line), 2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

/*
**	affiche la possibilite suivante grace un
**	pointeur static sur le maillon actuel
*/

void		display_next(t_group *grp, int comp_free)
{
	static char		*name = NULL;
	static t_comp	*last = NULL;
	char			*tmp2;
	char			*tmp;

	update_name(grp, &name, &last, comp_free);
	if (!grp->comp)
		return ;
	if (comp_free == 1)
		return ;
	if (grp->comp->c_type > 1 && grp->comp->type == C_COM)
		first_display(&last, grp, name);
	else if (grp->comp->c_type == 1 && grp->comp->type == C_COM)
		second_display(&last, grp, name);
	else if (grp->comp->c_type > 1)
		third_display(&last, grp);
	else if (grp->comp->c_type == 1)
		fourth_display(&last, grp);
}
