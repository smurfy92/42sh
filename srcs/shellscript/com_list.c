/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:15:45 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:11:02 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	cree un nouveau t_com avec tous les champs necessaires pour executer la
**	condition lors du read des actions
*/

/*
**	get la valeur des deux cotes de la comparaison et cree deux variables tmp
**	ou un pointeur vers le t_var si une variable connue est presenete dans la
**	comparaison
*/

static int			get_comp_vars(t_com *cmp, char *comp)
{
	char	**clean;
	int		i;

	clean = ft_strsplit(comp, cmp->type);
	i = 0;
	if (!clean[1])
	{
		ft_freestrtab(&clean);
		return (E_INCOMPLETE_COMP);
	}
	cmp->first = ft_strdup(clean[0]);
	cmp->second = ft_strdup(clean[1]);
	ft_freestrtab(&clean);
	return (0);
}

/*
**	verifie la validite de la comparaison => unicite
*/

static int			check_cmp_type(char *comp)
{
	int		i;
	int		ret;

	i = 0;
	ret = -1;
	while (comp[i])
	{
		if (comp[i] == '>')
			ret++;
		if (comp[i] == '<')
			ret++;
		if (comp[i] == '=')
			ret++;
		i++;
	}
	return (ret);
}

/*
**	get le type de la comp
**	comp->type = ASCII du char de comparaison
*/

static int			get_comp_type(char *comp, t_com *cmp)
{
	char	*tmp;
	int		ret;

	if (check_cmp_type(comp))
		return (E_MULTI_COMP);
	ret = 0;
	if ((tmp = ft_strchr(comp, '<')))
		ret += DIF_S;
	if ((tmp = ft_strchr(comp, '>')))
		ret += DIF_B;
	if ((tmp = ft_strchr(comp, '=')))
		ret += EQU_C;
	cmp->type = ret;
	return (0);
}

/*
**	cree le maillon comp, appelle tous les parsers necessaires
*/

t_com				*new_comparaison(char *comp, t_script *script)
{
	t_com	*new;

	new = (t_com *)malloc(sizeof(t_com));
	if ((script->errnb = get_comp_type(comp, new)))
		error_handler(script);
	if ((script->errnb = get_comp_vars(new, comp)))
		error_handler(script);
	return (new);
}
