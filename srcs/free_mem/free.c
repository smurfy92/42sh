/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:07 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/06 18:34:02 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		free_env(t_group *grp)
{
	t_envlst	*tmp3;
	t_envlst	*tmp4;

	tmp3 = grp->env->lst;
	tmp4 = NULL;
	while (tmp3 != NULL)
	{
		REMOVE(&tmp3->name);
		REMOVE(&tmp3->val);
		tmp4 = tmp3->next;
		free(tmp3);
		tmp3 = tmp4;
	}
	grp->env->lst = NULL;
}

void		free_env_tmp(t_group *grp)
{
	t_envlst	*tmp;
	t_envlst	*tmp2;

	grp->env->opt_i = false;
	grp->env->start_varenv = 0;
	grp->env->end_varenv = 0;
	tmp = grp->env->lst_tmp;
	tmp2 = NULL;
	while (tmp != NULL)
	{
		REMOVE(&tmp->name);
		REMOVE(&tmp->val);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	grp->env->lst_tmp = NULL;
	REMOVE(&ENV(cmd));
}

void		free_term(t_group *grp)
{
	t_cmdquote	*tmp;
	t_cmdquote	*tmp2;

	tmp = TERM(cmd_quote);
	tmp2 = NULL;
	while (tmp != NULL)
	{
		REMOVE(&tmp->line);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	TERM(cmd_quote) = NULL;
}

void		free_parselst(t_parse *parse)
{
	int			i;

	i = -1;
	ft_strdel(&(parse->cmd));
	while (parse->cmdsplit[++i])
		ft_strdel(&(parse->cmdsplit[i]));
	free(parse->cmdsplit);
	ft_strdel(&(parse->dbred));
	ft_strdel(&(parse->sgred));
	ft_strdel(&(parse->file));
	ft_strdel(&(parse->closefd));
	ft_strdel(&(parse->redfd));
	(parse->heredoc) ?
	ft_strdel(&(parse->heredoc)) : 0;
	free(parse);
	parse = NULL;
}

void		ft_free_parse(t_group *grp)
{
	free_term(grp);
	free_env_tmp(grp);
	check_parentheses(0);
}
