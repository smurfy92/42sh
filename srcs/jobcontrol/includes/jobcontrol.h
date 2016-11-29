/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobcontrol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:25:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/29 05:17:03 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBCONTROL_H
# define JOBCONTROL_H

typedef struct s_jobs
{
	int				idx;
	pid_t			pid;
	int				status;
	int				is_last;
	int				is_prelast;
	char			*cmd;
	int				terminate;
	struct s_jobs	*next;
}				t_jobs;

void		init_job_control(t_group *grp, t_andor *andor);
void		init_shell_job(int pgid);
int			builtin_jobs(t_group *grp);
int			builtin_fg(t_group *grp, int idx);
int			builtin_bg(void);
void		jobs_status(t_group *grp);
void		update_job(t_jobs *jobs);
void		jobs_states(t_group *grp);

#endif
