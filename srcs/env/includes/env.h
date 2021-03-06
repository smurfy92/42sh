/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:26:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/12 10:27:27 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef int				t_bool;

# define CMP(x, y)			ft_strcmp(x, y)

typedef struct			s_envlst
{
	char				*name;
	char				*val;
	t_bool				exist;
	struct s_envlst		*next;
}						t_envlst;

typedef struct			s_env
{
	struct s_envlst		*lst;
	struct s_envlst		*lst_tmp;
	t_bool				opt_i;
	int					start_varenv;
	int					end_varenv;
	char				*cmd;
	t_jobs				*pgid;
	int					fg;
	char				*path_tmp;
}						t_env;

/*
**	env .c
*/

int						builtin_env(t_group *grp, t_parse *parse);
void					shlvl(t_group *grp);
void					init_env(t_group *grp, char **env);

/*
**	env_lib.c
*/

int						is_env(char *env);
int						insert_env(t_group *grp, char *env);
int						insert_env_tmp(t_group *grp, char *env);
int						unset_env(t_group *grp, char *todel);
int						unset_env_tmp(t_group *grp, char *todel);
char					*ft_getenv(t_group *grp, char *tofind);
char					**list_to_tab(t_envlst *envlst);

/*
**	env_opt.c
*/

int						env_opt(t_group *grp, t_parse *parse);

/*
**	env_init.c
*/

void					help_shlvl(t_group *grp);
void					path_help(t_group *grp);
void					help_pwd(t_group *grp);
void					home_helper(t_group *grp);
void					under_helper(t_group *grp);

/*
**	env exec
*/

void					init_exec_env(t_group *grp);

#endif
