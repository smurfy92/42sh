/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 01:57:20 by vdanain           #+#    #+#             */
/*   Updated: 2016/11/13 01:57:38 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		free_hashcmd(t_path **cmd)
{
	t_path *tmp = *cmd;
	ft_strdel(&tmp->path);
	ft_strdel(&tmp->name);
	free(*cmd);
	*cmd = NULL;
}

void		hash_free(t_root **root, int len, t_hash *tmp)
{
	int			i;

	i = 0;
	while (i < len)
	{
		if (tmp->node[i])
			hash_free(root, len, tmp->node[i]);
		i++;
	}
	if (tmp->cmd != NULL)
		free_hashcmd(&tmp->cmd);
	free(tmp->node);
	tmp->node = NULL;
	free(tmp);
}

void		root_hfree(t_root **root)
{
	hash_free(root, ft_strlen((*root)->charlist), (*root)->first);
	ft_strdel(&(*root)->charlist);
	free(*root);
	root = NULL;
}
