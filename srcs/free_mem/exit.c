/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:02:54 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/13 19:04:13 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		exit_free_jobs(t_jobs **jobs)
{
	t_jobs	*tmp;
	t_jobs	*tp;

	tmp = *jobs;
	while (tmp)
	{
		tp = tmp->next;
		exit_free_jobs(&tmp->next_pipe);
		ft_strdel(&tmp->cmd);
		ft_strdel(&tmp->parent_cmd);
		ft_strdel(&tmp->status);
		free(tmp);
		tmp = tp;
	}
	*jobs = NULL;
}

void		ft_exit(t_group *grp, int exit_code)
{
	ft_free_parse(grp);
	free_env(grp);
	REMOVE(&TERM(cmd_line));
	root_hfree(&grp->root);
	free(TERM(window));
	free(grp->term);
	free(grp->env);
	free_history(grp);
	exit_free_jobs(&grp->jobs);
	check_parentheses(-4);
	exit_code ? exit_code : (exit_code = grp->exit);
	REMOVE(&grp->program_name);
	free(grp);
	exit(exit_code);
}
