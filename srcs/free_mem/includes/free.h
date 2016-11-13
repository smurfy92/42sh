/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:09:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 22:48:16 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

// free.c
void		free_env(t_group *grp);
void		ft_free_parse(t_group *grp);
void		ft_exit(t_group *grp, int exit_code);
void		free_parselst(t_parse *parse);
void		free_allparse(t_andor *begin);

//free2.c
void		ft_free_andor(t_group *grp);
void		free_history(t_group *grp);
void		free_term(t_group *grp);

#endif
