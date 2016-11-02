/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:29:47 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/02 18:06:46 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	ouvre et parcours les dossier de PATH
**	pour obtenir toutes les comandes
*/

void			fill_tree(t_root *root, DIR *cur_d, char *dir)
{
	struct dirent	*cur_e;
	t_path			*cur_p;
	char			*tmpath;

	while ((cur_e = readdir(cur_d)))
	{
		tmpath = get_fullpath(cur_e->d_name, dir);
		cur_p = init_path(cur_e->d_name, tmpath);
		init_cmd(cur_e->d_name, root, cur_p);
		ft_strdel(&tmpath);
	}
}

/*
**	Prend le nom d'une commande et le root pour creer un
**	node pour cette cmd
*/

void			init_cmd(char *cmd, t_root *root, t_path *path)
{
	t_hash	*tmp;
	int		i;

	i = 0;
	tmp = root->first;
	while (cmd[i])
	{
		if (tmp->node[val_tokey(root->charlist, cmd[i])] == NULL)
			tmp->node[val_tokey(root->charlist, cmd[i])] = node_init(cmd[i], ft_strlen(root->charlist));
		tmp = tmp->node[val_tokey(root->charlist, cmd[i])];
		i++;
	}
	tmp->cmd = path;
}

/*
**	init un node du t_hash, en lui attribuant uniquement une valeur
**	->char
*/

t_hash			*node_init(char c, int len)
{
	t_hash		*new;
	int			i;

	i = -1;
	new = (t_hash *)malloc(sizeof(t_hash));
	new->val = c;
	new->cmd = NULL;
	new->node = (t_hash **)malloc(sizeof(t_hash *) * (len + 1));
	while (++i <= len)
		new->node[i] = NULL;
	return (new);
}

/*
**	init le root
*/

t_root			*root_init(char *charlist)
{
	t_root		*new;

	new = (t_root *)malloc(sizeof(t_root));
	new->first = node_init(0, ft_strlen(charlist));
	new->charlist = ft_strdup(charlist);
	return (new);
}