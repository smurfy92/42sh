/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:07:29 by jtranchi          #+#    #+#             */
/*   Updated: 2016/10/31 23:27:00 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define H_SIZE 5000

typedef struct			s_group
{
	//history
	struct s_history		*history;
	int						inhistory;

	int						prompt_size;
	int						exit;
	struct s_parse			*parselst;
	struct s_window			*window;
	struct s_term			*term;
	struct termios			cpy_term;
	struct s_env			*env;
	struct s_hash			*hash[H_SIZE];

	//pas sur
	int						fail;
	int						minus;
}						t_group;

#endif
