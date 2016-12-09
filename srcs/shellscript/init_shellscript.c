/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shellscript.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:34:46 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:31:13 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	add_var_args(char **av, t_script *script)
{
	int			i;
	int			idx;
	t_assign	*new;
	char		*name;

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

int		init_shellscript(int ac, char **av, t_group *grp)
{
	char	*line;
	char	*buffer;
	t_script	*script;
	char		*tmp;
	char		**clean_s;
	int			i;

	i = 0;
	script = new_script();
	buffer = ft_strdup("");
	TERM(cmd_line) = ft_strdup("");
	if (ac >= 2)
	{
		if (ac > 2)
			add_var_args(av, script);
		if (((script->rd_fd = open(av[1], O_RDONLY)) < 0) && (script->errnb = E_WRONG_FILE))
			error_handler(script);
		while (get_next_line(script->rd_fd, &line))
		{
			tmp = ft_strtrim(line);
			buffer = ft_strjoin_nf(buffer, ";", 1);
			buffer = ft_strjoin_nf(buffer, tmp, 1);
			ft_strdel(&tmp);
			ft_strdel(&line);
		}
		clean_s = ft_strsplit(buffer, ';');
		if (main_checker(clean_s) == 0)
		{
			while (clean_s[i])
			{
				line_checker(clean_s, &i, script, &script->begin);
				if (script->errnb)
					break ;
				ft_putendl("");
				i++;
			}
		}
		ft_strdel(&buffer);
		ft_freestrtab(&clean_s);
		if (script->errnb)
			error_handler(script);
		display_action(script->begin);
		ft_putendl("starting reading actions");
		action_reader(script, script->begin);
		ft_putendl("end of reading");
		display_vars(script->vars);
		free_script(&script);
		grp->quit = true;
	}
	ft_putendl(TERM(cmd_line));
	ft_putendl("FINISHED");
	return (0);
}