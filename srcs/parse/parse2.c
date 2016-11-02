/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 15:27:24 by jtranchi          #+#    #+#             */
/*   Updated: 2016/10/27 15:27:25 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

// void		ft_check_close1(t_parse *parse, int i)
// {
// 	char *tmp;

// 	if (parse->cmd[i + 4])
// 	{
// 		tmp = ft_strdup(&parse->cmd[i + 4]);
// 		parse->cmd[i] = '\0';
// 		parse->cmd = ft_strjoin(parse->cmd, tmp);
// 	}
// 	else
// 		parse->cmd[i] = '\0';
// 	parse->close1 = 1;
// }

// void		ft_check_close2(t_parse *parse, int i)
// {
// 	char *tmp;

// 	if (parse->cmd[i + 4])
// 	{
// 		tmp = ft_strdup(&parse->cmd[i + 4]);
// 		parse->cmd[i] = '\0';
// 		parse->cmd = ft_strjoin(parse->cmd, tmp);
// 	}
// 	else
// 		parse->cmd[i] = '\0';
// 	parse->close2 = 1;
// }

//rajouter tilde pour replace vars

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
	//a revoir redirection de fd
	// if (ft_isdigit(parse->cmd[i]) && parse->cmd[i + 1] == '>' && parse->cmd[i + 2]
	// == '&' && parse->cmd[i + 3] && parse->cmd[i + 3] == '-')
	// 	ft_check_close1(parse, i);
	// else if (parse->cmd[i] == '2' && parse->cmd[i + 1] == '>' &&
	// parse->cmd[i + 2] == '&' && parse->cmd[i + 3] && parse->cmd[i + 3] == '-')
	// 	ft_check_close2(parse, i);
	// else
	if (parse->cmd[i] == '>' && parse->cmd[i + 1] &&
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
	else
		grp->minus = 1;
}

void		ft_parse_redirections(t_group *grp, t_parse *parse)
{
	int i;
	int ret;
	int test;

	i = 0;
	test = 0;
	while (parse->cmd[i])
	{
		grp->minus = 0;
		ret = check_parentheses(parse->cmd[i]);
		if (!ret)
		{
			//test = 1;
			ft_parse_redirections2(grp, parse, i);
		}
		else
		{
			printf("%c", parse->cmd[i]);
			i++;
		}
		if (grp->fail)
			break ;
		if (parse->sgred || parse->dbred)
			ft_create_redirections(parse);
		if (grp->minus)
			i++;
		
	}
}
