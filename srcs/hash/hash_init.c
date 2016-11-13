/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:19 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/13 02:21:04 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	join le nom de dossier et la commande pour un full path
*/

char			*get_fullpath(char *name, char *dir)
{
	char	*tmpath;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	tmpath = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (tmpath);
}

char			*fill_list(t_group *grp, char *cus_p)
{
	char	**path;
	char	*tmpath;
	char	*result;
	int		i;
	DIR		*cur_d;

	result = NULL;
	i = -1;
	if (!(tmpath = ft_getenv(grp, "PATH")) && cus_p == NULL)
		return (NULL);
	if (!(path = (cus_p == NULL) ? ft_strsplit(tmpath, ':') : ft_strsplit(cus_p, ':')))
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

int				tree_filler(t_root **root, t_group *grp, char *cus_p)
{
	char	**path;
	char	*tmpath;
	int		i;
	DIR		*cur_d;

	i = -1;
	if (!(tmpath = ft_getenv(grp, "PATH")) && cus_p == NULL)
		return (1);
	if (!(path = (cus_p == NULL) ? ft_strsplit(tmpath, ':') : ft_strsplit(cus_p, ':')))
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

int				hash_init(t_root **root, t_group *grp, char *cus_p)
{
	char	*result;

	if (!(result = fill_list(grp, cus_p)) || ft_strcmp(result, "") == 0)
		return (1);
	*root = root_init(result);
	if (tree_filler(root, grp, cus_p) != 0)
		return (1);
	return (0);
}
