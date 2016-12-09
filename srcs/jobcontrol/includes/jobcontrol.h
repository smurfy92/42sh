/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:25:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/09 06:38:12 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

typedef struct s_jobs
{
	pid_t			pid;
	int				idx;
	int				terminate;
	int				enabled;
	int				code;
	int				fdin;
	int				fg;
	char			*cmd;
	char			*parent_cmd;
	char			*status;
	struct s_jobs	*next_pipe;
	struct s_jobs	*next;
}				t_jobs;

/*
**	jobscreate.c
*/

t_jobs		*control_jobs(t_jobs **parent, t_group *grp, t_parse *parse, char *andorcmd);
t_jobs		*create_jobs(t_group *grp, t_jobs *new, char *cmd, int pid);
t_jobs		*create_pipe_jobs(t_jobs *new, t_jobs *jobs, char *cmd, int pid);
t_jobs		*get_jobs_idx(t_group *grp, int val);
t_jobs		*get_jobs_pid(t_group *grp, int pid);
void		display_jobs(t_jobs *jobs, int n, int parent);

/*
**	jobsbuiltins.c
*/

int			builtin_jobs(t_group *grp, char **cmd);
int			builtin_fg(t_group *grp, int idx);
int			builtin_bg(t_group *grp, int idx);
void		put_in_fg(t_group *grp, t_jobs *curr);

/*
**	jobsstatus.c
*/

void		jobs_update(t_group *grp);
void		jobs_status(t_group *grp);
void		change_state(t_jobs *jobs, int code);
void		analyse_ret(t_jobs *jobs, int ret, int code);
void		check_jobs_status(t_jobs *jobs);

#endif
