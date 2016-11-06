/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/05 16:36:00 by jmontija         ###   ########.fr       */
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
