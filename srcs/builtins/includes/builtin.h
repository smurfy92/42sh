/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/22 20:56:29 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define RPW(x, y) (ft_getenv(x, "PWD")) ? ft_getenv(x, "PWD") : getcwd(y, 1024)

/*
**	builtins.c
*/

int		builtins(t_group *grp, t_parse *parse);
int		builtin_cd(t_group *grp, t_parse *parse);
int		builtin_echo(t_group *grp, t_parse *parse);
int		is_builtins(char **cmd);

/*
**	cd_lib.c
*/

char	*clean_pwd(char **to_change);
char	*join_path(t_group *grp, char *path);
void	update_pwd(t_group *grp, char *pth, int opt, char *curr_dir);
void	cderr_pwd(t_group *grp, char **path, struct stat s_buf, int opt);
char	*starting_replace(char *path, char *replace, char *by);
char	*replace_in_path(t_group *grp, t_parse *parse, int nb);

/*
**	history.c
*/

int		builtin_history(t_group *grp, t_parse *parse);

/*
**	echo_lib.c
*/

char	*ft_charjoin(char *s1, char c);
int		octal_to_decimal(int octal_nb);

#endif
