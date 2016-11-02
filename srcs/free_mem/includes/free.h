/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:09:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/01 19:00:40 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

// free.c
void		free_env(t_group *grp);
void		ft_free_parse(t_group *grp);
void		ft_exit(t_group *grp, int exit_code);


#endif
