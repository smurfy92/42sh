/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:33:45 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 05:12:31 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"


static int		get_loop_type(char *line, t_loop *new)
{
	if (ft_strncmp(line, "while ", 6) == 0)
		new->type = LOOP_W;
	else
		return (E_INVALID_LOOP);
	return (0);
}

t_loop		*new_loop(char *text, t_script *script)
{
	int		i;
	char	**clean;
	t_loop	*new;

	i = 0;
	new = (t_loop *)malloc(sizeof(t_loop));
	new->comp = NULL;
	new->acts = NULL;
	clean = ft_strsplit(text, 135);
	while (clean[i])
	{
		if (i == 0)
		{
			if ((script->errnb = get_loop_type(clean[i], new)))
				error_handler(script);
			script->errnb = get_cond(clean[i], NULL, script, new);
		}
		if (i == 1 && ft_strcmp(clean[i], "do"))
			return (NULL);
		if (i > 1 && ft_strcmp(clean[i], "done"))
			line_checker(clean, &i, script, &new->acts);
		i++;
	}
	ft_freestrtab(&clean);
	return (new);
}
