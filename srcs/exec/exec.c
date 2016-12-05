/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 21:15:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/05 05:41:03 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

// void		check_lastcmd(t_group *grp, t_parse *parse, int fg)
// {
// 	t_parse		*tmp;
// 	t_jobs		*jobs;
// 	int			ret;
// 	int			is_built;

// 	tmp = parse;
// 	jobs = NULL;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	is_built = is_builtins(tmp->cmdsplit);
// 	if ((!is_built || !fg) && grp->is_interact) // 1ere cond a suppr
// 	{
// 		jobs = control_jobs(grp, parse, grp->father);
// 		setpgid (grp->father, grp->father);
// 	}
// 	if (is_built && parse->fd < 0)
// 	{
// 		waitpid(grp->father, &ret, 0);
// 		builtins(grp, tmp);
// 	}
// 	else if (grp->is_interact == false)
// 		waitpid(grp->father, &ret, 0);
// 	else if (fg)
// 		put_in_fg(grp, jobs);
// 	else
// 		sleep(1);
// }

// void		launch_exec(t_group *grp, t_parse *parse, int fg)
// {
// 	t_parse		*tmp;

// 	tmp = parse;
// 	grp->father = fork();
// 	grp->father < 0 ? ft_exit(grp, 999) : 0;
// 	if (grp->father == 0)
// 	{
// 		if (!is_builtins(tmp->cmdsplit))
// 			init_shell_job(grp->father, fg);
// 		while (tmp)
// 		{
// 			if (!tmp->fail)
// 				(tmp->next && tmp->fd == -1) ? ft_fork_pipe(grp, tmp) :
// 					exec_child(0, grp, tmp);
// 			tmp = tmp->next;
// 		}
// 		ft_exit(grp, EXIT_FAILURE);
// 	}
// 	else
// 		check_lastcmd(grp, parse, fg);
// }		

void		wait_jobs(t_jobs *parent)
{
	int		code;
	int		ret;
	t_jobs	*pipe;

	//printf("IN\n");
	while (42)
	{
		pipe = parent->next_pipe;
		ret = waitpid(parent->pid, &code, WNOHANG | WUNTRACED);
		if (ret && pipe == NULL)
		{
			printf("OUTPARENT\n");
			return ;
		}
		while (pipe)
		{
			ret = waitpid(pipe->pid, &code, WNOHANG | WUNTRACED);
			if (ret && pipe->next_pipe == NULL)
			{
				printf("OUTPIPE\n");
				return ;
			}
			pipe = pipe->next_pipe;
		}
	}
}

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
		if ((!is_built || tmp->next || tmp->fd > -1) && !tmp->fail)
		{
			pipe(tabl);
			grp->father = fork();
			grp->father < 0 ? ft_exit(grp, 999) : 0;
			if (grp->father == 0)
			{
				init_shell_job(grp->father, fg);
				if (tmp->next && tmp->fd == -1)
					ft_fork_pipe(grp, tmp, tabl[1]);
				else
					exec_child(0, grp, tmp);
				close(tabl[0]);
			}
			close(tabl[1]);
			grp->pipefd_in = tabl[0];
			jobs = control_jobs(&parent, grp, tmp);
			setpgid (parent->pid, grp->father); // reflchir a tout stocker dans
		}
		else if (is_built && tmp->fd < 0)
			builtins(grp, tmp);
		tmp = tmp->next;
	}
	parent ? display_jobs(parent, 1) : 0;
	if (fg && is_built == false)
	{
		tcsetpgrp(STDIN_FILENO, jobs->pid);
		wait_jobs(parent);
		tcsetpgrp(STDIN_FILENO, grp->program_pid);
	}
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
