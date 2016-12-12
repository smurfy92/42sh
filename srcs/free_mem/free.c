/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 23:30:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/12 07:41:39 by jmontija         ###   ########.fr       */
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
	REMOVE(&ENV(path_tmp));
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
	REMOVE(&(parse->cmd));
	while (parse->cmdsplit[++i])
		REMOVE(&(parse->cmdsplit[i]));
	free(parse->cmdsplit);
	REMOVE(&(parse->dbred));
	REMOVE(&(parse->sgred));
	REMOVE(&(parse->file));
	REMOVE(&(parse->closefd));
	REMOVE(&(parse->redfd));
	REMOVE(&(parse->bquotes));
	REMOVE(&(parse->heredoc));
	parse->fd = -1;
}

void		free_allparse(t_andor *andor)
{
	t_parse		*tmp;
	t_parse		*tmp2;

	tmp = andor->parselst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_parselst(tmp);
		free(tmp);
		tmp = tmp2;
	}
}
