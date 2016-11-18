/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 12:56:35 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/18 21:25:14 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void	error_cmd(char *what, char *who, int exit_code)
{
	t_group		*grp;

	grp = get_grp();
	ft_putstr_fd(what, 2);
	ft_putstr_fd(" -> ", 2);
	ft_putendl_fd(who, 2);
	grp->exit = exit_code;
}

int		error_env_opt(char opt, char *what)
{
	t_group		*grp;

	grp = get_grp();
	ft_putstr_fd("env:", 2);
	ft_putstr_fd(what, 2);
	ft_putchar_fd(opt, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd(
"usage: env [-i] [name=value] [utility [argument]", 2);
	grp->exit = 1;
	return (-1);
}

void	error_process_check(int error_code)
{
	t_group		*grp;

	grp = get_grp();
	error_code == SIGSEGV ? error_cmd("segmentation fault",
		grp->program_name, 1) : 0;
}
