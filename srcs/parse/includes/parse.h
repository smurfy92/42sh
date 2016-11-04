/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/04 13:57:34 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//struct

typedef	struct			s_parse
{
	char				*cmd;
	char				**cmdsplit;
	char				*dbred;
	char				*sgred;
	char				*heredoc;
	char				*file;
	int					fd;
	int					closefd;
	int					errnb;
	struct s_parse		*next;
}						t_parse;

//parse1.c

void					ft_create_parse(t_group *grp, char *cmd);
void					ft_parse2(t_group *grp);
void					ft_parse(t_group *grp, char *cmd);

//parse2.c

void					ft_check_close1(t_parse *parse, int i);
void					ft_check_close2(t_parse *parse, int i);
void					ft_replace_vars(t_group *grp, t_parse *parse, int i);
void					ft_parse_redirections2(t_group *grp, t_parse *parse,
int i);
void					ft_parse_redirections(t_group *grp, t_parse *parse);

//parse3.c

void					ft_copy_redirections(t_group *grp, t_parse *parse);
int						ft_count_pipes(char *cmd);
void					ft_create_redirections(t_parse *parse);

//parse4.c

void					ft_addredirectionsuite(t_parse *parse, int end,
int start);
void					ft_adddoubleredirection(t_group *grp, t_parse *parse,
int i);
void					ft_addredirection(t_group *grp, t_parse *parse, int i);
void					ft_addheredoc2(t_parse *parse, int end, int start);
void					ft_addheredoc(t_group *grp, t_parse *parse, int i);

//parse5.c

int						ft_is_space(char c);
void					ft_addfile(t_group *grp, t_parse *parse, int i);
int						ft_end_of_red(char c);
void					ft_redirection_error(t_parse *parse, int end);
int						ft_is_quote(char c);

//pre_parse.c
void					ft_pre_parse(t_group *grp);
void					ft_escape_parse(t_group *grp, int i);

#endif
