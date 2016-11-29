/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:07:29 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/29 23:08:09 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_group
{
	char					*program_name;
	pid_t					program_pid;
	int						is_interact;
	struct s_history		*history;
	int						inhistory;
	int						prompt_size;
	int						exit;
	int						quit;
	int						err_parse;
	int						hdcount;
	pid_t					father;
	struct s_allcmd			*allcmd;
	struct s_window			*window;
	struct s_term			*term;
	struct termios			cpy_term;
	struct termios			curr_term;
	struct s_env			*env;
	struct s_root			*root;
	struct s_comp			*comp;
	struct s_jobs			*jobs;
	int						fail;
	int						minus;
}						t_group;

#endif
