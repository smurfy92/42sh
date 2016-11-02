/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:02:54 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 14:22:41 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_free_hash(t_group *grp)
{
	int		i;
	t_hash	*tmp;
	t_hash	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (i < H_SIZE)
	{
		tmp = grp->hash[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			REMOVE(&tmp->name);
			REMOVE(&tmp->path);
			free(tmp);
			tmp = tmp2;
		}
		grp->hash[i] = NULL;
		i++;
	}
}

void		ft_exit(t_group *grp, int exit_code)
{
	ft_free_hash(grp);
	ft_free_parse(grp);
	//free grp;
	exit_code ? exit_code : (exit_code = grp->exit);
	free(grp);
	exit(exit_code);
}
