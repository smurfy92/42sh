/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 17:05:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/10/31 22:42:57 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_is_printable(char *order)
{
	int	i;

	i = -1;
	while (order[++i] != '\0')
		if (ft_isprint(order[i]) == false)
			return (0);
	return (1);
}

int		key_selection_next(t_group *grp, char *order, int key)
{
	if (key == HOME)
		ft_go_home(grp);
	else if (key == END)
		ft_go_end(grp);
	else if (key == ALT_L)
		ft_prev_word(grp);
	else if (key == ALT_R)
		ft_next_word(grp);
	else if (key == ARROW_L || key == ARROW_R ||
		key == ARROW_U || key == ARROW_D)
		handling_arrow(grp, key);
	else if (ft_is_printable(order))
		print_cmd(grp, order);
	else
		return (0);
	return (1);
}

int		key_selection(t_group *grp, char *order)
{
	int	key;

	key = KEY(order[0], order[1], order[2], order[3]);
	if (key == ENTER)
		return (key);
	// if (key != ARROW_U && key != ARROW_D)
	// 	grp->curr_hist = NULL;
	if (key == CTRL_D)
		handling_ctrl_d(grp);
	else if (key == DEL)
		remove_line(grp);
	else if (key == BACKSPACE || key == DEL)
		handling_backspace(grp);
	else if (key == CTRL_L)
		handling_clear_screen(grp);
	else if (key == PAGE_UP)
		ft_go_up(grp);
	else if (key == PAGE_DOWN)
		ft_go_down(grp);
	else
		return (key_selection_next(grp, order, key));
	return (1);
}

// void	read_fd_in(t_group *grp, char *order)
// {
// 	int	i;

// 	i = -1;
// 	while (order && order[++i] != '\0')
// 	{
// 		if (order[i] != '\n')
// 			TERM(cmd_line) = ft_charjoin(TERM(cmd_line), order[i]);
// 		else if (order[i + 1] != '\0')
// 			TERM(cmd_line) = JOIN(TERM(cmd_line), " ; ");
// 	}
// 	grp->exit[0] = true;
// }

int		check_last_char(char *line, int i)
{
	char	*tmp;
	int		count;

	if (i == 0)
		return (0);
	tmp = &line[i - 1];
	count = 0;
	i--;
	while (*tmp == '\\')
	{
		count++;
		if (i == 0)
			break;
		tmp = tmp - 1;
		i--;
	}
	printf("%d\n", count);
	if (count % 2 == 0)
		return (0);
	return (1);
}

int		check_esc(t_group *grp)
{
	int	i;
	int	ret;
	char c;

	i = -1;
	ret = -1;
	while (TERM(cmd_line) && TERM(cmd_line)[++i] != '\0')
	{
		c = TERM(cmd_line)[i];
		if ((c == '"' || c == '`') && check_last_char(TERM(cmd_line), i) == 0)
			ret = check_parentheses(c);
		else if (c != '"' && c != '`')
			ret = check_parentheses(c);
	}

	if (TERM(cmd_line) == NULL && TERM(cmd_quote) == NULL)
		return (0);
	return (ret);
}

void	fill_cmdquote(t_group *grp)
{
	t_cmdquote	*line;
	t_cmdquote	*tmp;

	tmp = TERM(cmd_quote);
	line = (t_cmdquote *)malloc(sizeof(t_cmdquote));
	line->line = TERM(cmd_line) ? SDUP(TERM(cmd_line)) : SDUP("");
	line->next = NULL;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = line;
	else
		TERM(cmd_quote) = line;
	TERM(curs_pos) = 0;
	TERM(line) = 0;
	TERM(cmd_size) = 0;
	TERM(other_read) = 0;
	REMOVE(&TERM(cmd_line));
}

void	fill_cmd_line(t_group *grp)
{
	t_cmdquote *tmp;

	fill_cmdquote(grp);
	tmp = TERM(cmd_quote);
	TERM(cmd_line) = SDUP("");
	while (tmp)
	{
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp->line, 1);
		TERM(cmd_line) = JOINF(TERM(cmd_line), "\n", 1);
		tmp = tmp->next;
	}
}

void	get_cmd(t_group *grp, int fd)
{
	int		ret;
	char	*tmp;
	char	order[BUF_SIZE + 1];

	tmp = NULL;
	ft_bzero(order, BUF_SIZE + 1);
	while ((ret = read(fd, order, BUF_SIZE)) > 0)
	{
		order[ret] = '\0';
		tmp = ft_strdup(order);
		if (key_selection(grp, order) == '\n')
		{
			if (check_esc(grp) == 0)
			{
				grp->prompt_size = 6;
				break ;
			}
			else
			{
				fill_cmdquote(grp);
				ft_putstr("\n$>");
				grp->prompt_size = 2;
			}
		}
		ft_bzero(order, BUF_SIZE + 1);
		ft_strdel(&tmp);
	}
	if (TERM(cmd_quote) != NULL)
		fill_cmd_line(grp);
	ft_go_end(grp);
	//ret == 0 ? read_fd_in(grp, tmp) :
	ft_putchar_fd('\n', 2);
	reset_edl(grp);
	ft_bzero(order, BUF_SIZE + 1);
	REMOVE(&tmp);
}
