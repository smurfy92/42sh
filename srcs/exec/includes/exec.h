/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:48 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 02:32:48 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void		init_exec(t_group *grp);
void		exec_child(t_group *grp, t_parse *parse);
void		ft_fork_pipe(t_group *grp);

#endif
