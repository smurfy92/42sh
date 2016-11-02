/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:43:24 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/01 17:53:40 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

typedef struct			s_cmdquote
{
	char				*line;
	int					noeof;
	struct s_cmdquote	*next;
}						t_cmdquote;

typedef struct			s_term
{
	char				*cmd_line;
	char				*cmd_save;
	char				*search;
	int					line;
	int					curs_pos;
	int					cmd_size;
	int					other_read;
	struct s_window		*window;
	struct s_cmdquote	*cmd_quote;
}						t_term;

void					get_cmd(t_group *grp, int fd);
void					ft_go_home(t_group *grp);
void					ft_go_end(t_group *grp);
void					ft_go_up(t_group *grp);
void					ft_go_down(t_group *grp);
void					up_clear_find(t_group *grp, char *name);
void					ft_replace_cursor(t_group *grp);
void					ft_get_cmd(t_group *grp, char *order);
void					print_cmd(t_group *grp, char *order);
void					handling_ctrl_d(t_group *grp);
void					handling_backspace(t_group *grp);
void					ft_left_arrow(t_group *grp);
void					ft_right_arrow(t_group *grp);
void					handling_arrow(t_group *grp, int key);
void					ft_prev_word(t_group *grp);
void					ft_next_word(t_group *grp);
void					handling_clear_screen(t_group *grp);
void					remove_line(t_group *grp);
void					reset_edl(t_group *grp);
int						ft_escape(t_group *grp);
void					fill_cmd_line(t_group *grp);

#endif
