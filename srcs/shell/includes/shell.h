/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:06 by jtranchi          #+#    #+#             */
/*   Updated: 2016/10/25 15:43:09 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef	struct			s_window
{
	int					width;
	int					heigth;
}						t_window;

//main.c
int						reset_shell(void);

// shell.c
void					prompt();
int						ft_getchar(int c);
void					init_env(t_group *grp, char **env);
int						init_shell(void);
void					init_exec(t_group *grp);
t_group					*set_grp(t_group *grp);
t_group					*get_grp(void);

//signaux.c
void					handler_win(int sig);
void					handler_ctrl_c(int sig);
void					ft_prompt(int signum);
void					sig_handler(void);

#endif
