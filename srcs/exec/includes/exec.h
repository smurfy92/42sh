/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:48 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/13 15:25:24 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*
**	exec.c
*/

void		init_exec(t_group *grp);

/*
**	exeve.c
*/

void		exec_child(t_group *grp, t_parse *parse);
void		exec_bquotes(t_group *grp, char *bquote);
void		ft_fork_pipe(t_group *grp, t_parse *parse, int pipefd_out);

/*
**	execlib.c
*/

void		generate_process(t_jobs **parent, t_parse *tmp,
									char *andorcmd, int fg);
void		generate_builtin(t_jobs **parent, t_parse *tmp,
									char *andorcmd, int fg);
void		ft_dup_redirection(t_parse *parse);
int			check_cmd(char **path, char *cmd);

#endif
