/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:15:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/07 04:52:57 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"	

void		launch_exec(t_group *grp, t_parse *parse, int fg)
{
	int		tabl[2];
	int		is_built;
	t_parse	*tmp;
	t_jobs	*jobs;
	t_jobs	*parent;

	tmp = parse;
	parent = NULL;
	is_built = false;
	grp->pipefd_in = STDIN_FILENO;
	while (tmp)
	{
		is_built = is_builtins(tmp->cmdsplit);
		if (!tmp->fail &&(!is_built || tmp->next || tmp->fd > -1))
		{
			pipe(tabl);
			grp->father = fork();
			grp->father < 0 ? ft_exit(grp, 999) : 0;
			if (grp->father == 0)
			{
				init_shell_job(parent ? parent->pid : 0, fg);
				if (tmp->next && tmp->fd == -1)
				{
					close(tabl[0]);
					ft_fork_pipe(grp, tmp, tabl[1]);
				}
				else
				{
					close(tabl[0]);
					close(tabl[1]);
					exec_child(grp, tmp);
				}
			}
			else
			{
				close(tabl[1]);
				grp->pipefd_in = tabl[0]; // pour les pipe verifier si tabl[0] toujours actif sinon broken pipe ! same for tabl[1]
				jobs = control_jobs(&parent, grp, tmp);
				setpgid (jobs->pid, parent->pid);
			}
		}
		else if (is_built && tmp->fd < 0)
			builtins(grp, tmp);
		if (tmp->fd > -1)
			break ;
		tmp = tmp->next;
	}
	parent ? display_jobs(parent, 1) : 0;
	if (grp->is_interact == false)
		waitpid(grp->father, NULL, 0);
	else if (fg && is_built == false)
		put_in_fg(grp, parent);
	else
		usleep(500);
}

void		create_fd(t_parse *parse)
{
	t_parse		*tmp;

	tmp = parse;
	while (tmp)
	{
		if (tmp->sgred || tmp->dbred)
			ft_create_redirections(tmp);
		tmp = tmp->next;
	}
}

void		andor_exec(t_group *grp, t_andor *andor)
{
	t_andor *tmp;

	tmp = andor;
	while (tmp)
	{
		reset_shell();
		create_fd(tmp->parselst);
		launch_exec(grp, tmp->parselst, (tmp->type == 3) ? 0 : 1);
		restore_shell();
		if ((tmp->type == 1 && grp->exit != 0) ||
			(tmp->type == 2 && grp->exit == 0))
			break ;
		if (tmp->next)
			grp->exit = 0;
		tmp = tmp->next;
	}
}

void		init_exec(t_group *grp)
{
	t_allcmd *tmp;

	tmp = grp->allcmd;
	if (!grp->fail)
	{
		grp->exit = 0;
		while (tmp)
		{
			andor_exec(grp, tmp->andor);
			tmp = tmp->next;
		}
	}
	free_allcmd(grp);
	grp->fail = 0;
}
