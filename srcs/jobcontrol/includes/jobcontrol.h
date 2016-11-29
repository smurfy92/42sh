/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:25:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 23:56:57 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

typedef struct s_jobs
{
	pid_t			pid;
	int				idx;
	int				terminate;
	int				is_last;
	int				is_prelast;
	struct termios	tmodes;
	char			*cmd;
	char			*status;
	char			**args;
	struct s_jobs	*next;
}				t_jobs;

void		init_job_control(t_group *grp, t_andor *andor);
int			builtin_jobs(t_group *grp);
int			builtin_fg(t_group *grp, int idx);
int			builtin_bg(void);
void		jobs_update(t_group *grp);
void		jobs_states(t_group *grp);
void		change_state(t_jobs *jobs, int code);

#endif
