/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 20:13:24 by vdanain           #+#    #+#             */
/*   Updated: 2016/10/31 23:24:23 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		val_tokey(char *name)
{
	int				i;
	long long int	res;
	int				my_res;

	i = 0;
	res = 0;
	while (name[i])
	{
		res += name[i] * (i * i);
		i++;
	}
	my_res = res % H_SIZE;
	return (my_res);
}

/*
**	get_path : accepte la cmd en argument, renvoie le full path si existe,
**	NULL sinon
*/

char	*get_path(char *cmd, t_hash *hash[H_SIZE])
{
	char	*path;
	t_hash	*cur;

	//cmd[ft_strlen(cmd) - 1] = '\0';
	cur = hash[val_tokey(cmd)];
	while (cur && ft_strncmp(cur->name, cmd, ft_strlen(cur->name)) != 0)
		cur = cur->next;
	if (cur)
	{
		path = ft_strdup(cur->path);
		return (path);
	}
	else
		return (NULL);
}
