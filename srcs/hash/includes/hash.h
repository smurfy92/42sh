/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:16:14 by vdanain           #+#    #+#             */
/*   Updated: 2016/10/31 23:28:01 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define H_SIZE 5000

typedef	struct		s_hash
{
	char			*name;
	char			*path;
	struct s_hash	*next;
}					t_hash;

/*
**	hash_use.c
*/

int					val_tokey(char *name);
char				*get_path(char *cmd, t_hash *hash[H_SIZE]);

/*
**	hash_init.c
*/

void				clean_hash(t_hash *hash[H_SIZE]);
int					hash_init(t_hash *my_hash[H_SIZE]);

#endif
