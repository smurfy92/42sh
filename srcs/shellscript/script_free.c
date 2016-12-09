/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 03:57:13 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:09:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		assign_free(void **to_free)
{
	t_assign	*tmp;

	ft_putendl("ASSIGN FREEING");
	tmp = *to_free;
	ft_strdel(&tmp->name);
	ft_strdel(&tmp->value);
	free(tmp);
	*to_free = NULL;
}

void		line_free(void **to_free)
{
	t_line	*tmp;

	ft_putendl("LINE FREEING");
	tmp = *to_free;
	ft_strdel(&tmp->cmd);
	free(*to_free);
	*to_free = NULL;
}

void		sc_comp_free(t_com **to_free)
{
	t_com	*tmp;

	ft_putendl("COMP FREEING");
	tmp = *to_free;
	if (tmp)
	{
		ft_putendl("1");
		ft_putendl(tmp->first);
		ft_strdel(&tmp->first);
		ft_putendl("1");
		ft_strdel(&tmp->second);
		ft_putendl("1");
		free(tmp);
	}
	ft_putendl("ENDED COMP");
	*to_free = NULL;
}

void		condition_free(void **to_free)
{
	t_cond	*tmp;
	t_cond	*tp;

	tmp = *to_free;
	ft_putendl("COND FREEING");
	while (tmp)
	{
		tp = tmp->next;
		ft_strdel(&tmp->text);
		action_free(&tmp->acts);
		sc_comp_free(&tmp->comp);
		free(tmp);
		tmp = tp;
	}
	*to_free = NULL;
}
