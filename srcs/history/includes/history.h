/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 18:49:31 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/18 22:44:10 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef	struct			s_history
{
	char				*var;
	int					i;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

/*
**	history.c
*/

void					ft_add_history(t_group *grp, char *cmd);
void					ft_history_prev(t_group *grp);
void					ft_history_next(t_group *grp);
void					ft_get_history(t_group *grp);

/*
**	hist_lib.c
*/

t_history				*ft_history_get_last(t_group *grp);
t_history				*ft_history_get_first(t_group *grp);
t_history				*ft_history_get_by_id(t_group *grp, int nb);

#endif
