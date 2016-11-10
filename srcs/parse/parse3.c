/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:29:42 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/10 23:11:05 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

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

// void		ft_create_heredoc2(t_group *grp, char *str, int fd, int i)
// {
// 	grp->inheredoc = 1;
// 	grp->cmdlength = ft_strlen(grp->cmdactual) - 12;
// 	ft_go_end(grp);
// 	(i == 0) ? ft_putstr_fd("heredoc-> ", 2) : ft_putstr_fd("\nheredoc-> ", 2);
// 	while (42)
// 	{
// 		ft_reset_term(grp);
// 		while ((read(0, grp->buf, BUFFSIZE)) && grp->buf[0] != 10)
// 		{
// 			if (!grp->inheredoc)
// 				break ;
// 			ft_process(grp);
// 			if (!grp->inheredoc)
// 				break ;
// 		}
// 		if (!grp->inheredoc)
// 		{
// 			reset_shell();
// 			break ;
// 		}
// 		if (ft_strequ(grp->cmdactual, str))
// 			break ;
// 		ft_putendl_fd(grp->cmdactual, fd);
// 		ft_putstr_fd("\nheredoc-> ", 2);
// 	}
// }

// void		ft_create_heredoc(t_group *grp)
// {
// 	int		i;
// 	char	**tabl;
// 	char	*tmp;

// 	i = -1;
// 	tabl = ft_strsplit(grp->parselst->heredoc, ';');
// 	while (tabl && tabl[++i])
// 	{
// 		tmp = ft_strjoin(ft_get_env_by_name(grp, "HOME"), "/");
// 		tmp = ft_strjoin_nf(tmp, ".21shheredoctmp", 1);
// 		grp->heredocfd = open(tmp, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC,
// 		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
// 		ft_strdel(&tmp);
// 		ft_create_heredoc2(grp, tabl[i], grp->heredocfd, i);
// 		ft_strdel(&tabl[i]);
// 	}
// 	free(tabl);
// 	ft_putchar_fd('\n', 2);
// 	close(grp->heredocfd);
// 	if (!grp->parselst->file)
// 	{
// 		tmp = ft_strjoin(ft_get_env_by_name(grp, "HOME"), "/");
// 		grp->parselst->file = ft_strjoin_nf(tmp, ".21shheredoctmp", 1);
// 	}
// 	grp->inheredoc = 0;
// }
