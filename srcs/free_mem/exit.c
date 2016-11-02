/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:02:54 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/02 18:07:49 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void		ft_exit(t_group *grp, int exit_code)
{
	ft_free_parse(grp);
	free_env(grp);
	REMOVE(&TERM(cmd_line));
	free(TERM(window));
	free(grp->term);
	free(grp->env);
	free_history(grp);
	exit_code ? exit_code : (exit_code = grp->exit);
	free(grp);
	exit(exit_code);
}
