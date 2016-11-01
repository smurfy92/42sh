/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:19 by vdanain           #+#    #+#             */
/*   Updated: 2016/10/31 15:15:18 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static char		*get_fullpath(char *name, char *dir)
{
	char	*tmpath;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	tmpath = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (tmpath);
}

static void		hash_fill(t_hash *first, char *name, char *path)
{
	t_hash	*cur;

	if (first->next == NULL && ft_strcmp("", first->name) == 0)
	{
		ft_strdel(&first->name);
		first->name = ft_strdup(name);
		ft_strdel(&first->path);
		first->path = ft_strdup(path);
		return ;
	}
	else
	{
		cur = first;
		while (cur->next != NULL || ft_strcmp("", cur->name) == 0)
			cur = cur->next;
		cur->next = (t_hash *)malloc(sizeof(t_hash));
		cur->next->name = ft_strdup(name);
		cur->next->path = (path == NULL) ? NULL : ft_strdup(path);
		cur->next->next = NULL;
		return ;
	}
}

static void		init_help(t_hash *my_hash[H_SIZE], char *path, DIR *cur_d)
{
	struct dirent	*cur_e;
	char			*tmpath;

	while ((cur_e = readdir(cur_d)))
	{
		if (ft_strcmp(".", cur_e->d_name) != 0
			&& ft_strcmp("..", cur_e->d_name) != 0)
		{
			tmpath = get_fullpath(cur_e->d_name, path);
			hash_fill(my_hash[val_tokey(cur_e->d_name)], cur_e->d_name, tmpath);
			ft_strdel(&tmpath);
		}
	}
}

/*
**	initialise la table de hash
**	errcode : 1 = No path env, < 0 = err during opening dir form path
*/

void			clean_hash(t_hash *hash[H_SIZE])
{
	int		i;

	i = 0;
	while (i < H_SIZE)
	{
		hash[i] = (t_hash *)malloc(sizeof(t_hash));
		hash[i]->name = ft_strdup("");
		hash[i]->path = ft_strdup("");
		hash[i]->next = NULL;
		i++;
	}
}

int				hash_init(t_hash *my_hash[H_SIZE])
{
	char	**path;
	char	*tmpath;
	int		i;
	DIR		*cur_d;
	int		error;

	i = -1;
	error = 0;
	clean_hash(my_hash);
	if (!(tmpath = getenv("PATH")))
		return (1);
	path = ft_strsplit(tmpath, ':');
	clean_hash(my_hash);
	while (path[++i])
	{
		if (!(cur_d = opendir(path[i])))
			error--;
		else
		{
			init_help(my_hash, path[i], cur_d);
			closedir(cur_d);
		}
	}
	ft_freestrtab(&path);
	return (error);
}
