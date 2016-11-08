/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:16:14 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/08 19:04:36 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

typedef struct		s_path
{
	char			*name;
	char			*path;
}					t_path;

typedef	struct		s_hash
{
	char			val;
	struct s_hash	**node;
	t_path			*cmd;
}					t_hash;

typedef struct		s_root
{
	char			*charlist;
	t_hash			*first;
}					t_root;
/*
**	hash_use.c
*/
char				*get_path(char *cmd, t_root *root);

/*
**	hash_init.c
*/

int					val_tokey(char *charlist, char c);
int					hash_init(t_root **root, t_group *grp);
char				*get_fullpath(char *name, char *dir);

/*
**	tree_init.c
*/

void				fill_tree(t_root *root, DIR *cur_d, char *dir);
void				init_cmd(char *cmd, t_root *root, t_path *path);
t_hash				*node_init(char c, int len);
t_root				*root_init(char *charlist);

/*
**	tree_init2.c
*/

t_path				*init_path(char *name, char *path);
int					val_tokey(char *charlist, char c);
char				*get_nbchar(DIR *cur_d);

#endif
