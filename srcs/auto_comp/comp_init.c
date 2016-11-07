/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:40:40 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/04 13:02:32 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"
#include "termcaps.h"

char		*get_last_word(char *cmd)
{
		return ((!ft_strrchr(cmd, ' ')) ? cmd : ft_strrchr(cmd, ' '));
}


void	new_possible(char *value, t_comp *root, int is_d)
{
	t_comp	*new;

	new = (t_comp *)malloc(sizeof(t_comp));
	new->val = ft_strdup(value);
	new->next = root->next;
	new->is_d =  is_d;
	new->prev = root;
	root->next = new;
	new->next->prev = new;
}

int		rundir(char *to_open, t_comp *root)
{
	struct dirent	*cur_e;
	DIR				*dir;
	int				i;

	i = 0;
	if (!(dir = opendir(to_open)))
		return (1);
	while ((cur_e = readdir(dir)))
	{
		if (cur_e->d_name[0] != '.')
		{
			if (ft_strlen(root->val) == 1 || ft_strncmp(root->val + 1, cur_e->d_name, ft_strlen(root->val) - 1) == 0)
				new_possible(cur_e->d_name, root, ((cur_e->d_type & DT_DIR) == DT_DIR) ? 1 : 0);
			i++;
		}
	}
	root->size = i;
	return (0);
}

int		complete_val(t_comp *root)
{
	if (ft_strncmp(root->val, " /", 2) == 0)
		;
	else
		rundir(".", root);
	return (0);
}

int		get_possible(char *go, t_comp *root)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(go, " ") == 0)
		ret = rundir(".", root);
	else if (ft_strlen(go) > 1)
	{
		// ft_putendl("popopo");
		complete_val(root);
	}
	return (ret);
}



void		display_possible(t_comp *curr, t_group *grp, t_comp *root)
{
	char *tmp;
	char *tmp2;
	static int	index = 0;

	if (root == curr)
		return;
	index = (index == 0) ? TERM(curs_pos) : index;
	tmp2 = ft_strsub(TERM(cmd_line), 0, index);
	tmp = ft_strjoin(tmp2, curr->val);
	// ft_strdel(&TERM(cmd_line));
	remove_line(grp);
	TERM(cmd_line) = ft_strdup(tmp);
	TERM(curs_pos) = ft_strlen(TERM(cmd_line));
	TERM(cmd_size) = ft_strlen(TERM(cmd_line));
	ft_putstr_fd(TERM(cmd_line), 2);
	ft_strdel(&tmp);
}


void		root_display(t_comp *root, t_group *grp, int key)
{
	static t_comp	*tmp = NULL;
	char			buff[5];

	ft_bzero(buff, 5);
	tmp = (tmp == NULL) ? root->next : tmp->next;
	if (key)
		;
	while (read(0, buff, 5))
	{
		display_possible(tmp, grp, root);
		tmp = tmp->next;
		if (BUFF(buff) != TAB)
		{
			grp->comp = NULL;
			if (key_selection(grp, buff) == '\n' && ft_escape(grp) == 0)
				break ;
		}
		// ft_putstr("P : ");
		// ft_putnbr(tmp->is_d);
		// ft_putendl(tmp->val);
	}
}

t_comp		*new_root(char *cmd)
{
	t_comp	*root;

	root = (t_comp *)malloc(sizeof(t_comp));
	root->val = ft_strdup(get_last_word(cmd));
	root->size = 0;
	root->next = root;
	root->prev = root;
	get_possible(root->val, root);
	return (root);
}

void comp_init(t_group *grp, int key)
{

	grp->comp = (grp->comp == NULL) ? new_root(TERM(cmd_line)) : grp->comp;
	root_display(grp->comp, grp, key);
}