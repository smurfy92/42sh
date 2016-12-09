/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 23:53:50 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:09:44 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void				ft_my_trim(char **to_trim)
{
	char	*tmp;

	tmp = ft_strtrim(*to_trim);
	ft_strdel(to_trim);
	*to_trim = tmp;
}

/*
**	handler de l'assignation d'une variable, traite la chaine de caractere
**	de lassignation pour attribuer un type et une value a la var
*/

/*
**	deduit le type lors d'une assignation
*/

static int			type_guesser(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (STR_T);
		i++;
	}
	return (NUMBER_T);
}

/*
**	make sure only one operation per assignation
*/

static int			check_op(char *value)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if ((tmp = ft_strchr(value, '+')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '+')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '/')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '/')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '*')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '*')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '-')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '-')) ? ret += 2 : ret++;
	if ((tmp = ft_strchr(value, '%')))
		(*(tmp + 1) && ft_strchr(tmp + 1, '%')) ? ret += 2 : ret++;
	return (ret);
}

/*
**	handler de l'assignation simple
*/

static void	*simple_assignator(char *value, int *type)
{
	int		*ret;

	*type = type_guesser(value);
	if (*type == STR_T)
		return ((void *)value);
	ret = (int *)malloc(sizeof(int));
	*ret = ft_atoi(value);
	return ((void *)ret);
}

static void	*handler_numb_op(char **clean, char op, int *type)
{
	char	*ret;
	void	*r_ret;

	*type = NUMBER_T;
	ret = NULL;
	r_ret = NULL;
	if (op == '+')
	{
		ret = ft_itoa(ft_atoi(clean[0]) + ft_atoi(clean[1]));
		r_ret = simple_assignator(ret, type);
	}
	if (op == '-')
	{
		ret = ft_itoa(ft_atoi(clean[0]) - ft_atoi(clean[1]));
		r_ret = simple_assignator(ret, type);
	}
	if (op == '*')
	{
		ret = ft_itoa(ft_atoi(clean[0]) * ft_atoi(clean[1]));
		r_ret = simple_assignator(ret, type);
	}
	if (op == '/')
	{
		if (ft_atoi(clean[1]) == 0)
			return (NULL);
		ret = ft_itoa(ft_atoi(clean[0]) / ft_atoi(clean[1]));
		r_ret = simple_assignator(ret, type);
	}
	if (op == '%')
	{
		ret = ft_itoa(ft_atoi(clean[0]) % ft_atoi(clean[1]));
		r_ret = simple_assignator(ret, type);
	}
	ft_strdel(&ret);
	return (r_ret);
}

static void	*handler_str_conc(char **clean, int *type)
{
	char	*ret;

	*type = STR_T;
	ret = ft_strjoin(clean[0], clean[1]);
	ft_putendl(ret);
	return ((void *)ret);
}

static void	*handler_op(char *value, int *type, char op)
{
	char		**clean;
	int			types[2];
	void		*ret;

	ret = NULL;
	clean = ft_strsplit(value, op);
	if (!clean[1])
	{
		ft_freestrtab(&clean);
		return (NULL);
	}
	ft_my_trim(&clean[0]);
	ft_my_trim(&clean[1]);
	var_replacer(get_script(NULL), &clean[0]);
	var_replacer(get_script(NULL), &clean[1]);
	types[0] = type_guesser(clean[0]);
	types[1] = type_guesser(clean[1]);
	ft_putendl("ICI CEST LOUUUURD");
	if (types[0] == types[1] && types[0] == NUMBER_T)
		ret = handler_numb_op(clean, op, type);
	if (types[0] == types[1] && types[0] == STR_T && op == '+')
	{
		ft_putendl("CONCATENATION ACTIVATED");
		ret = handler_str_conc(clean, type);
	}
	ft_freestrtab(&clean);
	return (ret);
}



/*
**	handler de l'assignation
*/

void	*assignator(t_assign *assign, int *type)
{
	if (!assign->value)
		return (NULL);
	if (check_op(assign->value) > 1)
		return (NULL);
	if (ft_strchr(assign->value, '+'))
		return (handler_op(assign->value, type, '+'));
	else if (ft_strchr(assign->value, '-'))
		return (handler_op(assign->value, type, '-'));
	else if (ft_strchr(assign->value, '*'))
		return (handler_op(assign->value, type, '*'));
	else if (ft_strchr(assign->value, '/'))
		return (handler_op(assign->value, type, '/'));
	else if (ft_strchr(assign->value, '%'))
		return (handler_op(assign->value, type, '%'));
	else
	{
		var_replacer(get_script(NULL), &assign->value);
		return (simple_assignator(assign->value, type));
	}
}