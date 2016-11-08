/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victordanain <victordanain@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:39:35 by victordanain      #+#    #+#             */
/*   Updated: 2016/11/08 19:29:14 by victordanain     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"



// #elif __linux__
// # define HELP_PATH linux_pathhelp()

// "/usr/libexec/path_helper"
/*
** recupere le path avec env-i
*/

char	*mac_pathhelp(void)
{
	pid_t		father;
	int			fd;

	father = fork();
	if (father == 0)
	{
		fd = open(".pathhelp", O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd, 1);
		execve("/usr/libexec/path_helper", NULL, NULL);
		close (fd);
		exit(0);
	}
	else
	{
		wait(0);
		fd = open(".pathhelp", O_RDONLY);
		
		close(fd);
	}
	return (NULL);
}
