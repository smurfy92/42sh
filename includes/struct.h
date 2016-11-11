/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:07:29 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/11 16:38:46 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_group
{
	//history
	struct s_history		*history;
	int						inhistory;

	int						prompt_size;
	int						exit;
	int						hdcount;
	pid_t					father;
	struct s_allcmd			*allcmd;
	struct s_window			*window;
	struct s_term			*term;
	struct termios			cpy_term;
	struct s_env			*env;
	struct s_root			*root;

	//pas sur
	int						fail;
	int						minus;
}						t_group;

#endif
