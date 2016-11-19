/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/18 22:33:14 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	get_path : accepte la cmd en argument, renvoie le full path si existe,
**	NULL sinon
*/

char		*gp(char *cmd, t_root *root)
{
	t_hash	*cur;
	int		i;
	char	*path;

	i = 0;
	cur = root->first;
	while (cmd[i])
	{
		cur = cur->node[val_tokey(root->charlist, cmd[i])];
		i++;
		if (cur == NULL)
			return (NULL);
	}
	if (cur->cmd == NULL)
		return (NULL);
	path = ft_strdup(cur->cmd->path);
	return (path);
}

char		*get_path(char *cmd, t_root *root)
{
	char		*tmpath;

	if (cmd == NULL || ft_strcmp(cmd, "") == 0)
		return (NULL);
	if (root == NULL || !root->first)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (ft_strcmp((tmpath = gp(ft_strrchr(cmd, '/') + 1, root)), cmd) == 0)
			return (tmpath);
		else
		{
			ft_strdel(&tmpath);
			return (NULL);
		}
	}
	else
		return (gp(cmd, root));
}

/*
**	return the starting node for auto-comp
*/

t_hash		*get_startnode(char *cmd, t_root *root)
{
	t_hash	*cur;
	int		i;

	i = 0;
	cur = root->first;
	while (cmd[i])
	{
		cur = cur->node[val_tokey(root->charlist, cmd[i])];
		i++;
		if (cur == NULL)
			return (NULL);
	}
	return (cur);
}

/*
**	remplis la static pour get_possible
*/

static void	result_filler(char **result, t_hash *cur)
{
	char	*tmp;
	char	*tmp2;

	tmp = ((*result) == NULL) ? ft_strdup("") : ft_strdup((*result));
	if ((*result))
		ft_strdel(result);
	tmp2 = ft_strjoin(tmp, " ");
	(*result) = ft_strjoin(tmp2, cur->cmd->name);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

/*
**	get all possibilities from a node in the tree : auto-comp
*/

char		*get_possible(t_hash *start, size_t len, int comp_free)
{
	t_hash		*cur;
	static char	*result = NULL;
	char		*tmp;
	char		*tmp2;
	size_t		i;

	if (comp_free == 1)
		ft_strdel(&result);
	cur = start;
	i = -1;
	if (cur->cmd != NULL)
		result_filler(&result, cur);
	while (++i < len)
	{
		if (cur->node[i])
			get_possible(cur->node[i], len, 0);
	}
	return (result);
}
