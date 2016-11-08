/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/06 18:15:20 by jmontija         ###   ########.fr       */
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
	char				*closefd;
	char				*redfd;
	int					errnb;
	struct s_parse		*next;
}						t_parse;

typedef struct		s_allcmd
{
	char			*cmd; // cmd ;
	struct s_andor	*andor;
	struct s_allcmd	*next;
}					t_allcmd;

typedef struct		s_andor
{
	char			*cmd;
	int				type;
	struct s_parse	*parselst;
	struct s_andor	*next;
}					t_andor;

//parse1.c

void					ft_create_parse(t_group *grp, t_andor *tabl, t_andor *andor);
void					ft_parse2(t_andor *andor);
void					ft_parse(t_group *grp, t_andor *andor);

//parse2.c

void					ft_replace_vars(t_group *grp, t_parse *parse, int i);
void					ft_parse_redirections2(t_group *grp, t_parse *parse,
int i);
void					ft_parse_redirections(t_group *grp, t_parse *parse);

//parse3.c

void					ft_copy_redirections(t_group *grp, t_parse *parse);
int						ft_count_pipes(char *cmd);
void					ft_create_redirections(t_parse *parse);
void					ft_replace_tilde(t_group *grp, t_parse *parse, int i);

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

//heredoc.c
void					check_heredoc(t_group *grp);

//split
t_allcmd				*ft_strsplitquote(char *s, char c);
t_andor					*ft_strsplitpipe(char *s, char c);
t_andor					*ft_strsplitandor(char *s);

#endif
