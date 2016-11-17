/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:48 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 17:00:33 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void		init_exec(t_group *grp);
void		exec_child(t_group *grp, t_parse *parse);
void		ft_fork_pipe(t_group *grp, t_parse *parse);
void		ft_dup_redirection(t_parse *parse);
int			check_cmd(char **path, char *cmd);

#endif
