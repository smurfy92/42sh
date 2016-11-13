/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 13:07:22 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 03:07:00 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

//errors.c
void	error_cmd(char *what, char *who, int err_code);
int		error_env_opt(char opt, char *what);
void	error_process_check(int error_code);

#endif
