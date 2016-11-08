/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fortytwo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:42:31 by jtranchi          #+#    #+#             */
/*   Updated: 2016/11/08 16:58:19 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTYTWO_H
# define FORTYTWO_H

# include <stdio.h>
# include <term.h>
# include <curses.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "struct.h"
# include "hash.h"
# include "shell.h"
# include "env.h"
# include "builtin.h"
# include "parse.h"
# include "exec.h"
# include "termcaps.h"
# include "history.h"
# include "free.h"
# include "debug.h"
# include "errors.h"

# define BUFFSIZE 6
# define KEY(a, b, c, d) ((d << 24) + (c << 16) + (b << 8) + a)
# define NEW(x)			(ft_strnew(x))
# define LEN(x)			(ft_strlen(x))
# define SDUP(x)		(ft_strdup(x))
# define SUB(a, b, c)	(ft_strsub(a, b, c))
# define JOIN(a, b)		(ft_strjoin(a, b))
# define JOINF(a, b, c)	(ft_strjoin_nf(a, b, c))
# define STRCHR(a, b)	(ft_strchr(a, b))
# define REMOVE(x)		(ft_strdel(x))
# define ENV(x)			((grp->env)->x)
# define CMD(x)			((grp->parselst)->x)
# define TERM(x)		((grp->term)->x)
# define KEY(a, b, c, d) ((d << 24) + (c << 16) + (b << 8) + a)
# define BUF_SIZE 4096
# define START_POS grp->prompt_size
# define ENTER 10
# define SPACE 32
# define TAB 9
# define ESC 27
# define ARROW_L 4479771
# define ARROW_U 4283163
# define ARROW_R 4414235
# define ARROW_D 4348699
# define ALT_L 1146821403
# define ALT_R 1130044187
# define BACKSPACE 127
# define DEL 2117294875
# define CTRL_D 4
# define CTRL_L 12
# define CTRL_R 18
# define CTRL_V 22
# define PAGE_UP 2117425947
# define PAGE_DOWN 2117491483
# define HOME 4741915
# define END 4610843

#endif
