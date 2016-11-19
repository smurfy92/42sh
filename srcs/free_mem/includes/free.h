/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:09:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/19 15:58:12 by vdanain          ###   ########.fr       */
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
void		free_allcmd(t_group *grp);

//free2.c
void		ft_free_andor(t_group *grp);
void		free_history(t_group *grp);
void		free_term(t_group *grp);
void		free_env_tmp(t_group *grp);

#endif
