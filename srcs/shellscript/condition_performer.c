/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_performer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:30:50 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:11:55 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"


static t_var	*get_comp_var(char *value, int idx)
{
	t_var		*tmp;
	t_assign	*tp;
	int			type;
	void		*val;
	char		*name;

	name = ft_itoa(idx);
	name = ft_strjoin_nf("tmp_", name, 2);
	tp = new_assignation(name, value);
	val = assignator(tp, &type);
	if (!val)
	{
		assign_free((void **)&tp);
		ft_strdel(&name);
		get_script(NULL)->errnb = E_INCOMPLETE_COND;
		error_handler(get_script(NULL));
	}
	tmp = new_var(type, val, tp->name);
	assign_free((void **)&tp);
	ft_strdel(&name);
	return (tmp);
}

static int		get_comp_value(t_com *cmp, t_var *fst, t_var *scd)
{
	if (cmp->type == EQU_C && fst->type == STR_T)
	{
		if (ft_strcmp(fst->str, scd->str) == 0)
			return (0);
	}
	else if (cmp->type == EQU_C)
	{
		if (*fst->nb == *scd->nb)
			return (0);
	}
	else if (cmp->type == DIF_S)
	{
		if (*fst->nb < *scd->nb)
			return (0);
	}
	else if (cmp->type == DIF_B)
	{
		if (*fst->nb > *scd->nb)
			return (0);
	}
	return (-1);
}

int				comp_analyzer(t_com *cmp)
{
	t_var	*fst;
	t_var	*scd;
	int		ret;

	fst = get_comp_var(cmp->first, 1);
	scd = get_comp_var(cmp->second, 2);
	if (fst->type != scd->type)
		return ((get_script(NULL)->errnb = E_INCOMPLETE_COND));
	else if (cmp->type != EQU_C && fst->type == STR_T)
		return ((get_script(NULL)->errnb = E_INCOMPLETE_COND));
	ret = get_comp_value(cmp, fst, scd);
	vars_free(&fst);
	vars_free(&scd);
	return (ret);
}

int				perform_condition(t_cond *current, t_script *script)
{
	int		ret;

	ret = 0;
	if (current->type == COND_ELSE ||
		(ret = comp_analyzer(current->comp)) == 0)
		action_reader(script, current->acts);
	else if (ret > 0)
		error_handler(script);
	return (ret);
}

