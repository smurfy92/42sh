/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:07:29 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 20:37:56 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_group
{
	char					*program_name;
	
	//history
	struct s_history		*history;
	int						inhistory;

	int						prompt_size;
	int						exit;
	int						quit;
	int						hdcount;
	pid_t					father;
	struct s_allcmd			*allcmd;
	struct s_window			*window;
	struct s_term			*term;
	struct termios			cpy_term;
	struct s_env			*env;
	struct s_root			*root;
	struct s_comp			*comp;

	//pas sur
	int						fail;
	int						minus;
}						t_group;

#endif
