/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:07:29 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/06 18:34:33 by jmontija         ###   ########.fr       */
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
	struct s_parse			*parselst;
	struct s_andor			*andor;
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
