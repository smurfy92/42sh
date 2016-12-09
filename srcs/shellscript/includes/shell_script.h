/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_script.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:29:28 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 07:05:10 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SCRIPT_H
# define SHELL_SCRIPT_H

# define LAST(x) x[ft_strlen(x) - 1]

# define TRUE				1
# define FALSE				0

/*
**	action : assignation dune variable
*/

typedef struct		s_assign
{
	char			*name;
	char			*value;	
}					t_assign;

/*
**	action : ligne de commande
*/

typedef struct		s_line
{
	char			*cmd;
}					t_line;

/*
**	structure maillon de la liste d'action
*/


typedef struct		s_action
{
	int				type;
	void			*action;
	struct s_action	*next;
}					t_action;

/*
**	Types d'action
*/

# define ASSIGN_T			1
# define LINE_T				2
# define COND_T				3
# define LOOP_T				4

/*
**	variable
*/

typedef struct		s_var
{
	int				type;
	char			*name;
	int				*nb;
	char			*str;
	struct s_var	*next;
}					t_var;


/*
**	Types de variable
*/

# define STR_T				1
# define NUMBER_T			2

/*
**	structure comparaison
*/

typedef struct		s_com
{
	char			*first;
	char			*second;
	int				type;
}					t_com;

/*
**	Types comparaisons
*/

# define EQU_C				61
# define DIF_S				60
# define DIF_B				62

/*
**	LOOPS struct
*/

typedef struct		s_loop
{
	int				type;
	// char			*text;
	t_com			*comp;
	t_action		*acts;
}					t_loop;

/*
**	types de loop
*/

# define LOOP_W		1
# define LOOP_F		2

/*
**	struct condition
*/

typedef struct		s_cond
{
	int				type;
	char			*text;
	t_com			*comp;
	t_action		*acts;
	struct s_cond	*next;
}					t_cond;


/*
**	types condition
*/

# define COND_IF			1
# define COND_ELIF			2
# define COND_FI			3
# define COND_ELSE			4
# define COND_LOOP			5


/*
**	struct root
*/

typedef struct		s_script
{
	int				fd;
	t_action		*begin;
	t_var			*vars;
	int				errnb;
	int				rd_fd;
	int				idx;
}					t_script;

/*
**	errnos
*/

# define E_TOO_EQU			1
# define E_INSTANT			2
# define E_CONF_TYPES		3
# define E_UNKNOWN_VAR		4
# define E_INCOMPLETE_COND	5
# define E_STARTED_COND		6
# define E_MULTI_COMP		7
# define E_INCOMPLETE_COMP	8
# define E_INVALID_OP		9
# define E_INVALID_LOOP		10
# define E_WRONG_FILE		11
/*
**	script_free.c
*/

void				free_script(t_script **script);
void				action_free(t_action **begin);
void				vars_free(t_var **to_free);
void				assign_free(void **to_free);
void				sc_comp_free(t_com **to_free);
void				condition_free(void **to_free);
void				line_free(void **to_free);

/*
**	debug.c
*/

void				display_action(t_action *begin);
void				display_vars(t_var *begin);

/*
**	condition_make.c
*/

int					condition_maker(char *line, t_script *script, t_action **begin);

/*
**	loop_list.c
*/

t_loop				*new_loop(char *text, t_script *script);

/*
**	condition_performer.c
*/

int					perform_condition(t_cond *current, t_script *script);
int					comp_analyzer(t_com *cmp);

/*
**	cond_list.c
*/

t_cond				*new_cond(char *text, t_script *script, t_cond **begin);
int					get_cond(char *line, t_cond *cond, t_script *script, t_loop *loop);

/*
**	com_list.c
*/

t_com				*new_comparaison(char *comp, t_script *script);

/*
**	check_lib.c
*/

int					main_checker(char **check);
int					is_important_space(char *line);

/*
**	action_reader.c
*/

void				action_reader(t_script *script, t_action *begin);

/*
**	assignator.c
*/

void				*assignator(t_assign *assign, int *type);

/*
**	error.c
*/

void				error_handler(t_script *script);

/*
**	var_list.c
*/

void				add_to_list(t_script *script, t_assign *assign);
t_var				*check_if_var_exists(char *name, t_script *script);
t_var				*new_var(int type, void *data, char *name);
void				ft_strreplace(char **line, char *old, char *new);

/*
**	script_lib.c
*/

void				str_join_init(char *str);

/*
**	checker.c
*/

int					line_checker(char **clean, int *i, t_script *script, t_action **begin);

/*
**	script.c
*/

t_script			*get_script(t_script *script);
t_script			*new_script(void);

/*
**	action_list.c
*/

void				add_to_action(void *action, t_script *script,  int type, t_action **begin);
void				add_to_action_cond(void *action, t_cond *cond, int type);

/*
**	assign.c
*/

t_assign			*new_assignation(char *name, char *value);

/*
**	var_replacer.c
*/

void				var_replacer(t_script *script, char **line);

int					init_shellscript(int ac, char **av, t_group *grp);

#endif