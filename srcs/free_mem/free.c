/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 15:10:07 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/13 23:31:23 by vdanain          ###   ########.fr       */
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

void		free_allparse(t_andor *begin)
{
	t_parse		*tmp;
	t_parse		*tmp2;

	tmp = begin->parselst;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_strdel(&(tmp->cmd));
		ft_freestrtab(&tmp->cmdsplit);
		ft_strdel(&(tmp->dbred));
		ft_strdel(&(tmp->sgred));
		ft_strdel(&(tmp->file));
		ft_strdel(&(tmp->closefd));
		ft_strdel(&(tmp->redfd));
		(tmp->heredoc) ?
		ft_strdel(&(tmp->heredoc)) : 0;
		tmp->fd = -1;
		free(tmp);
		tmp = tmp2;
	}
	begin->parselst = NULL;
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
	parse->fd = -1;
	free(parse);
	parse = NULL;
}

void	free_allandor(t_andor **to_free)
{
	t_andor	*tmp;
	t_andor	*tmp2;

	tmp = *to_free;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_strdel(&tmp->cmd);
		if (tmp->parselst)
			free_allparse(tmp);
		tmp->parselst = NULL;
		free(tmp);
		tmp = tmp2;
	}
	*to_free = NULL;
}

void	free_allcmd(t_allcmd **to_free)
{
	t_allcmd	*tmp;
	t_allcmd	*tmp2;

	tmp = *to_free;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_strdel(&tmp->cmd);
		if (tmp->andor)
			free_allandor(&tmp->andor);
		free(tmp);
		tmp = tmp2;
	}
	*to_free = NULL;
}

void		ft_free_parse(t_group *grp)
{
	char	*file;

	free_term(grp);
	free_env_tmp(grp);
	check_parentheses(0);
	if (grp->allcmd)
		free_allcmd(&grp->allcmd);
	while (grp->hdcount > 0)
	{
		file = JOINF("hdoc_", ft_itoa(grp->hdcount), 2);
		unlink(file);
		REMOVE(&file);
		grp->hdcount -= 1;
	}
}
