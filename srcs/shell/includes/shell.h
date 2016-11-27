/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:06 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/27 23:18:32 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef	struct			s_window
{
	int					width;
	int					heigth;
}						t_window;

/*
**	shell.c
*/

void					prompt();
int						ft_getchar(int c);
int						init_shell(void);
int						reset_shell(void);
t_group					*set_grp(t_group *grp);
t_group					*get_grp(void);

/*
**	signaux.c
*/

void					handler_win(int sig);
void					handler_ctrl_c(int sig);
void					ft_prompt(int signum);
void					sig_handler(void);

/*
**	prompt.c
*/

void					prompt(void);

#endif
