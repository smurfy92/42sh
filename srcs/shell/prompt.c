/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:25:26 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/22 16:42:54 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

static void		prompt_path(t_group *grp)
{
	char		*str;
	char		*str2;
	char		*str3;

	if (ft_getenv(grp, "PWD"))
	{
		str = SDUP(ft_getenv(grp, "PWD"));
		str2 = SDUP(ft_getenv(grp, "HOME"));
		if (str2 && ft_strstr(str, str2))
		{
			str3 = ft_strjoin("~", &str[ft_strlen(str2)]);
			ft_putstr_fd(str3, 2);
			grp->prompt_size += ft_strlen(str3);
			REMOVE(&str3);
		}
		else
		{
			ft_putstr_fd(str, 2);
			grp->prompt_size += ft_strlen(str);	
		}
		REMOVE(&str);
		REMOVE(&str2);
	}
}

void			prompt(void)
{
	t_group		*grp;

	grp = get_grp();
	grp->prompt_size = 0;
	if (grp->quit == false)
	{
		if (!grp->exit)
			ft_putstr_fd("\033[92m",2);
		else
			ft_putstr_fd("\033[91m",2);
		if (ft_getenv(grp, "LOGNAME") != NULL)
		{
			ft_putstr_fd(ft_getenv(grp, "LOGNAME"), 2);
			grp->prompt_size += ft_strlen(ft_getenv(grp, "LOGNAME"));
		}
		else
		{
			ft_putstr_fd("42sh", 2);
			grp->prompt_size += 4;
		}
		ft_putstr_fd(":(", 2);
		prompt_path(grp);
		ft_putstr_fd(") > \033[0m", 2);
		grp->prompt_size += 6;
	}
	//grp->prompt_size = 6;
}