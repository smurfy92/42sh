/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 16:17:44 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/12 03:42:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

// int		check_file(t_group *grp, char *name)
// {
// 	struct stat	s_buf;
// 	mode_t		val;
// 	int			ret;

// 	ret = lstat(name, &s_buf);
// 	val = (s_buf.st_mode & ~S_IFMT);
// 	if (ret != 0)
// 		error_cmd("unknown file", name);
// 	else if (!(val & S_IRUSR))
// 		error_cmd("Permission denied", name);
// 	else if (!S_ISREG(s_buf.st_mode))
// 		error_cmd("file required", name);
// 	else
// 		return (0);
// 	return (-1);
// }

void		ft_replace_vars(t_group *grp, t_parse *parse, int i)
{
	int		start;
	char	*tmp;
	char	*tmp2;

	start = i;
	while (parse->cmd[i] && ft_isalpha(parse->cmd[i]))
		i++;
	tmp = ft_strsub(&parse->cmd[start], 0, i - start);
	if (ft_getenv(grp, tmp) == NULL)
		grp->minus = 1;
	else
	{
		tmp2 = ft_strdup(&parse->cmd[i]);
		parse->cmd[start - 1] = '\0';
		if (!parse->cmd[start + 1])
			parse->cmd = ft_strjoin_nf(parse->cmd, ft_getenv(grp, tmp), 1);
		else
			parse->cmd = JOINF(JOINF(parse->cmd,
			ft_getenv(grp, tmp), 1), tmp2, 1);
		ft_strdel(&tmp2);
		ft_strdel(&tmp);
	}
}

void		ft_create_redirections(t_parse *parse)
{
	if (parse->sgred)
		parse->fd = open(parse->sgred, O_WRONLY |
		O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (parse->dbred)
		parse->fd = open(parse->dbred, O_WRONLY | O_CREAT |
		O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
}

int			ft_count_pipes(char *cmd)
{
	int i;
	int nb;
	int	ret;

	nb = 1;
	i = -1;
	ret = 0;
	while (cmd && cmd[++i])
	{
		ret = check_parentheses(cmd[i]);
		if (ret == 0 && cmd[i] == '|' && (i > 0 && cmd[i - 1] != '\\'))
			nb++;
	}
	return (nb);
}

void		ft_replace_tilde(t_group *grp, t_parse *parse, int i)
{
	char	*path;
	char	*tmp;

	path = ft_getenv(grp, "HOME");
	if (path == NULL)
		ft_putendl_fd("Your stupid theres no home", 2);
	tmp = SDUP(&parse->cmd[i + 1]);
	parse->cmd[i] = '\0';
	if (parse->cmd[i + 1])
	{
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 1);
	}
	else
		parse->cmd = ft_strjoin_nf(parse->cmd, path, 1);
	REMOVE(&tmp);
	grp->minus = 1;
}