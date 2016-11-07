/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:40:45 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/03 21:41:05 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMP_H
# define COMP_H

#define BUFF(x) *(unsigned int *)x

typedef struct		s_comp
{
	char			*val;
	int				is_d;
	int				size;

	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

void		comp_init(t_group *grp, int key);

#endif