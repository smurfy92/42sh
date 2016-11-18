/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:40:45 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/18 17:57:37 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMP_H
# define COMP_H

# define BUFF(x) *(unsigned int *)x

# define C_DIR DT_DIR
# define C_REG DT_REG
# define C_COM 2
# define C_OTH 3

# define CIS_D(x) (x & C_DIR) == C_DIR ? 1 : 0
# define CIS_C(x) (x & C_COM) == C_COM ? 1 : 0
# define CIS_O(x) (x & C_OTH) == C_OTH ? 1 : 0

typedef struct		s_comp
{
	char			*val;
	int				c_type;
	int				start;
	int				type;

	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

/*
**	comp_lib.c
*/

char				*get_last_word(char *cmd);
void				point_onlast(char **lw);
char				*get_dirtop(char *cmd);
void				update_name(t_group *gp, char **na, t_comp **la, int c);

/*
**	comp_init.c
*/

void				comp_init(t_group *grp, t_comp **comp);
void				comp_free(t_group *grp, t_comp **begin);
t_comp				*rtcomp_init(int start, char *val);

/*
**	comp_list.c
*/

t_comp				*new_comp(char *val, t_comp **begin, int type, int start);

/*
**	comp_use.c
*/

void				display_next(t_group *grp, int comp_free);

/*
**	com_finder.c
*/

void				cmd_finder(t_group *grp, t_comp **comp);
int					file_finder(t_group *grp, char *dir, t_comp **comp);

#endif
