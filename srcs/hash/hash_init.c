/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:19 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/02 18:32:25 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	join le nom de dossier et la commande pour un full path
*/

char		*get_fullpath(char *name, char *dir)
{
	char	*tmpath;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	tmpath = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (tmpath);
}

char			*fill_list()
{
	char	**path;
	char	*tmpath;
	char	*result;
	int		i;
	DIR		*cur_d;

	result = NULL;
	i = -1;
	if (!(tmpath = getenv("PATH")))
		return (NULL);
	if (!(path = ft_strsplit(tmpath, ':')))
		return (NULL);
	while (path[++i])
	{
		if ((cur_d = opendir(path[i])))
		{
			result = get_nbchar(cur_d);
			closedir(cur_d);
		}
	}
	ft_freestrtab(&path);
	return (result);
}

int				tree_filler(t_root **root)
{
	char	**path;
	char	*tmpath;
	int		i;
	DIR		*cur_d;

	i = -1;
	if (!(tmpath = getenv("PATH")))
		return (1);
	if (!(path = ft_strsplit(tmpath, ':')))
		return (1);
	while (path[++i])
	{
		if ((cur_d = opendir(path[i])))
		{
			fill_tree(*root, cur_d, path[i]);
			closedir(cur_d);
		}
	}
	ft_freestrtab(&path);
	return (0);
}

int				hash_init(t_root **root)
{
	char	*result;

	if (!(result = fill_list()) || ft_strcmp(result, "") == 0)
		return (1);
	*root = root_init(result);
	if (tree_filler(root) != 0)
		return (1);
	return (0);
}