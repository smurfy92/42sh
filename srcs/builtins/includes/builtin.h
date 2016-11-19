/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:50:41 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 20:00:45 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
**	builtins.c
*/

int		builtins(t_group *grp, t_parse *parse);
int		builtin_cd(t_group *grp, t_parse *parse);
int		builtin_echo(t_group *grp, t_parse *parse);
int		is_builtins(char **cmd);

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
