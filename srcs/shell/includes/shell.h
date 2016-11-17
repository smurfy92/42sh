/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:06 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 17:02:04 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef	struct			s_window
{
	int					width;
	int					heigth;
}						t_window;

// shell.c
void					prompt();
int						ft_getchar(int c);
int						init_shell(void);
int						reset_shell(void);
t_group					*set_grp(t_group *grp);
t_group					*get_grp(void);

//signaux.c
void					handler_win(int sig);
void					handler_ctrl_c(int sig);
void					ft_prompt(int signum);
void					sig_handler(void);

#endif
