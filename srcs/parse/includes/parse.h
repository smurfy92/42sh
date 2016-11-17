/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:57 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/17 17:02:10 by julio            ###   ########.fr       */
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
	char				*bquotes;
	int					fd;
	char				*closefd;
	char				*redfd;
	int					errnb;
	int					fail;
	struct s_parse		*next;
}						t_parse;

typedef struct			s_allcmd
{
	char				*cmd; // cmd ;
	struct s_andor		*andor;
	struct s_allcmd		*next;
}						t_allcmd;

typedef struct			s_andor
{
	char				*cmd;
	int					type;
	struct s_parse		*parselst;
	struct s_andor		*next;
}						t_andor;

//init_parse.c

void					ft_init_parse(t_group *grp);

//redirections.c

void					ft_parse_redirections(t_group *grp, t_parse *parse);

//redirections2.c

void					ft_addheredoc(t_group *grp, t_parse *parse, int i);
void					ft_check_close(t_parse *parse, int i);
void					ft_check_redirection_fd(t_parse *parse, int i);

//redirections_lib.c

char					*get_redirection(t_group *grp, t_parse *parse, int i, int start);
int						check_rights(t_parse *parse, char **file, int i);
void					ft_redirection_error(t_parse *parse, int end);

//parse_lib.c.c

void					ft_replace_vars(t_group *grp, t_parse *parse, int i);
void					ft_create_redirections(t_parse *parse);
int						ft_count_pipes(char *cmd);
void					ft_replace_tilde(t_group *grp, t_parse *parse, int i);
void					ft_replace_bquote(t_parse *parse, int i);
//parse_lib2.c

int						ft_is_quote(char c);
int						ft_is_space(char c);
int						ft_end_of_red(char c);
void					ft_redirection_error(t_parse *parse, int end);

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
