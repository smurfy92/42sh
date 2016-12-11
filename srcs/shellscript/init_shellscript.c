/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shellscript.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:34:46 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/11 19:42:46 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		add_var_args(char **av, t_script *script, int ac)
{
	int			i;
	int			idx;
	t_assign	*new;
	char		*name;

	if (ac == 2)
		return ;
	i = 2;
	idx = 1;
	while (av[i])
	{
		name = ft_itoa(idx);
		new = new_assignation(name, av[i]);
		add_to_list(script, new);
		ft_strdel(&name);
		assign_free((void **)&new);
		i++;
		idx++;
	}
}

static char		*get_text_script(t_script *script)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (get_next_line(script->rd_fd, &line))
	{
		tmp = ft_strtrim(line);
		buffer = ft_strjoin_nf(buffer, ";", 1);
		buffer = ft_strjoin_nf(buffer, tmp, 1);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	return (buffer);
}

static int		fill_action_list(char *buffer, t_script *script)
{
	char	**clean_s;
	int		i;

	i = 0;
	clean_s = ft_strsplit(buffer, ';');
	if (main_checker(clean_s) == 0)
	{
		while (clean_s[i])
		{
			line_checker(clean_s, &i, script, &script->begin);
			if (script->errnb)
				break ;
			i++;
		}
		return (script->errnb);
	}
	else
		return (1);
}

static int		script_exec(t_script *script, t_group *grp)
{
	action_reader(script, script->begin);
	if (!script->errnb)
	{
		ft_pre_parse(grp);
		if (grp->err_parse == false && TERM(cmd_line))
		{
			grp->allcmd = ft_strsplitquote(TERM(cmd_line), ';');
			ft_init_parse(grp);
			if (grp->err_parse == false)
				init_exec(grp);
			remove_hdoc(grp);
			ft_free_parse(grp);
			free(grp->allcmd);
			return (0);
		}
	}
	ft_strdel(&TERM(cmd_line));
	return (1);
}

int				init_shellscript(int ac, char **av, t_group *grp)
{
	char		*buffer;
	t_script	*script;
	int			i;

	i = 0;
	script = new_script();
	TERM(cmd_line) = ft_strdup("");
	if (ac >= 2)
	{
		add_var_args(av, script, ac);
		if (((script->rd_fd = open(av[1], O_RDONLY)) < 0) &&
			(script->errnb = E_WRONG_FILE))
			error_handler(script);
		buffer = get_text_script(script);
		if (fill_action_list(buffer, script))
		{
			ft_strdel(&buffer);
			error_handler(script);
		}
		ft_strdel(&buffer);
		script_exec(script, grp);
		free_script(&script);
		ft_exit(grp, grp->exit);
	}
	return (0);
}
