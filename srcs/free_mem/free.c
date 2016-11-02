/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:07 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/01 19:48:52 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		free_env(t_group *grp)
{
	t_envlst	*tmp;
	t_envlst	*tmp2;

	grp->env->opt_i = false;
	grp->env->start_varenv = 0;
	grp->env->end_varenv = 0;
	tmp = grp->env->lst_tmp;
	tmp2 = NULL;
	while(tmp != NULL)
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
	while(tmp != NULL)
	{
		REMOVE(&tmp->line);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	TERM(cmd_quote) = NULL;
}

void		free_parselst(t_group *grp)
{
	t_parse		*parse;
	int			i;

	while (grp->parselst)
	{
		i = -1;
		ft_strdel(&(grp->parselst->cmd));
		while (grp->parselst->cmdsplit[++i])
			ft_strdel(&(grp->parselst->cmdsplit[i]));
		free(grp->parselst->cmdsplit);
		ft_strdel(&(grp->parselst->dbred));
		ft_strdel(&(grp->parselst->sgred));
		ft_strdel(&(grp->parselst->file));
		(grp->parselst->heredoc) ?
		ft_strdel(&(grp->parselst->heredoc)) : 0;
		parse = grp->parselst->next;
		free(grp->parselst);
		grp->parselst = parse;
	}
	if (grp->parselst)
	{
		free(grp->parselst);
		grp->parselst = NULL;
	}
}

void		ft_free_parse(t_group *grp)
{
	free_parselst(grp);
	free_term(grp);
	free_env(grp);
}
