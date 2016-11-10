/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:27:24 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/10 23:47:28 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_check_close(t_parse *parse, int i)
{
	char	*tmp;
	char	*fd;

	fd = ft_strsub(parse->cmd, i, 1);
	if (parse->cmd[i + 4])
	{
		tmp = ft_strdup(&parse->cmd[i + 4]);
		parse->cmd[i] = '\0';
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i] = '\0';
	if (parse->closefd)
	{
		parse->closefd = ft_strjoin_nf(parse->closefd, ";", 1);
		parse->closefd = ft_strjoin_nf(parse->closefd, fd, 1);
	}
	else
		parse->closefd = ft_strdup(fd);
	REMOVE(&fd);
}

void		ft_check_redirection_fd(t_parse *parse, int i)
{
	char	*tmp;
	char	*fd;
	char	*fd2;

	fd2 = ft_strsub(parse->cmd, i + 3, 1);
	fd = ft_strsub(parse->cmd, i, 1);
	if (parse->cmd[i + 4])
	{
		tmp = ft_strdup(&parse->cmd[i + 4]);
		parse->cmd[i] = '\0';
		parse->cmd = ft_strjoin_nf(parse->cmd, tmp, 3);
	}
	else
		parse->cmd[i] = '\0';
	fd = ft_strjoin_nf(fd, ">", 1);
	fd = ft_strjoin_nf(fd, fd2, 3);
	if (parse->redfd)
		REMOVE(&parse->redfd);
	parse->redfd = ft_strdup(fd);
	REMOVE(&fd);
}

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

void		ft_parse_redirections2(t_group *grp, t_parse *parse, int i)
{
	if (ft_isdigit(parse->cmd[i]) && parse->cmd[i + 1] == '>' &&
	parse->cmd[i + 2] == '&' && parse->cmd[i + 3] && parse->cmd[i + 3] == '-')
		ft_check_close(parse, i);
	else if (ft_isdigit(parse->cmd[i]) && parse->cmd[i + 1] == '>' &&
	parse->cmd[i + 2] == '&' && parse->cmd[i + 3] &&
	ft_isdigit(parse->cmd[i + 3]))
		ft_check_redirection_fd(parse, i);
	else if (parse->cmd[i] == '>' && parse->cmd[i + 1] &&
	parse->cmd[i + 1] == '>')
		ft_adddoubleredirection(grp, parse, i + 2);
	else if (parse->cmd[i] == '>')
		ft_addredirection(grp, parse, i + 1);
	else if (parse->cmd[i] == '<' && parse->cmd[i + 1] &&
	parse->cmd[i + 1] == '<')
		ft_addheredoc(grp, parse, i + 2);
	else if (parse->cmd[i] == '<')
		ft_addfile(grp, parse, i + 1);
	else if (parse->cmd[i] == '$' && parse->cmd[i + 1])
		ft_replace_vars(grp, parse, i + 1);
	else if (parse->cmd[i] == '~')
		ft_replace_tilde(grp, parse, i);
	else
		grp->minus = 1;
}

void		ft_parse_redirections(t_group *grp, t_parse *parse)
{
	int i;
	int ret;

	i = 0;
	check_parentheses(0);
	while (parse->cmd[i])
	{
		grp->minus = 0;
		ret = check_parentheses(parse->cmd[i]);
		if (!ret && (i == 0 || parse->cmd[i - 1] != '\\'))
			ft_parse_redirections2(grp, parse, i);
		else
			i++;
		if (grp->fail)
			break ;
		if (parse->sgred || parse->dbred)
			ft_create_redirections(parse);
		if (grp->minus)
			i++;
	}
}
