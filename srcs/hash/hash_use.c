/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/08 19:09:19 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	get_path : accepte la cmd en argument, renvoie le full path si existe,
**	NULL sinon
*/

char	*get_path(char *cmd, t_root *root)
{
	t_hash	*cur;
	int		i;
	char	*path;

	i = 0;
	if (cmd == NULL || ft_strcmp(cmd, "") == 0)
		return (NULL);
	if (root == NULL)
		return (NULL);
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
**	get all possibilities from a node in the tree : auto-comp
*/

char		*get_possible(t_hash *start, size_t len)
{
	t_hash		*cur;
	static char	*result = NULL;
	char		*tmp;
	char		*tmp2;
	size_t		i;

	cur = start;
	i = -1;
	if (cur->cmd != NULL)
	{
		tmp = (result == NULL) ? ft_strdup("") : ft_strdup(result);
		if (result)
			ft_strdel(&result);
		tmp2 = ft_strjoin(tmp, " ");
		result = ft_strjoin(tmp2, cur->cmd->name);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	while (++i < len)
	{
		if (cur->node[i])
			get_possible(cur->node[i], len);
	}
	return (result);
}
