/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:48 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/25 01:17:22 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void		init_exec(t_group *grp);
void		exec_child(int jobs, t_group *grp, t_parse *parse);
void		exec_bquotes(t_group *grp, t_parse *parse);
void		ft_fork_pipe(t_group *grp, t_parse *parse);
void		ft_dup_redirection(t_parse *parse);
int			check_cmd(char **path, char *cmd);
int 		check_redirections_rights(t_andor *andor);

#endif
