/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:09:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 14:31:30 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

// free.c
void		free_env(t_group *grp);
void		ft_free_parse(t_group *grp);
void		ft_exit(t_group *grp, int exit_code);
void		free_history(t_group *grp);

#endif
