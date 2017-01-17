/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 22:44:21 by vdanain           #+#    #+#             */
/*   Updated: 2017/01/17 14:03:25 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

char		*clean_pwd(char **to_change)
{
	char	*cur;
	int		i;
	int		j;
	char	*pwd;

	i = 0;
	j = 0;
	pwd = *to_change;
	cur = (char *)malloc(sizeof(char) * (ft_strlen(pwd) + 1));
	while (pwd[i])
	{
		while (pwd[i] == '/' && pwd[i + 1] && pwd[i + 1] == '/')
			i++;
		cur[j] = pwd[i];
		j++;
		i++;
	}
	cur[j] = '\0';
	REMOVE(to_change);
	*to_change = cur;
	return (cur);
}

char		*join_path(t_group *grp, char *path)
{
	char	*tmp;
	char	*result;
	char	buff[1024 + 1];

	ft_bzero(buff, 1025);
	tmp = ft_strjoin("PWD=", (ft_getenv(grp, "PWD")) ?
		ft_getenv(grp, "PWD") : getcwd(buff, 1024));
	if (tmp[ft_strlen(tmp) - 1] != '/')
		tmp = JOINF(tmp, "/", 1);
	result = JOIN(tmp, path);
	ft_strdel(&tmp);
	return (result);
}

void		replce_last_s(char *cd, int len)
{
	if (*cd == '/' && len > 1)
		*cd = '\0';
}

void		update_pwd(t_group *grp, char *pth, int opt, char *cd)
{
	char	*pwd;
	char	*old_pwd;
	char	buf[1024 + 1];
	char	*tp;

	ft_bzero(buf, 1025);
	old_pwd = JOIN("OLDPWD=", cd);
	pth[LEN(pth) - 1] = (pth[LEN(pth) - 1] == '/' && LEN(pth) - 1 != 0) ?
		'\0' : pth[LEN(pth) - 1];
	tp = (ft_getenv(grp, "PWD")) ? ft_getenv(grp, "PWD") : getcwd(buf, 1024);
	if (!opt && ft_strncmp(pth, "..", 2) != 0 && ft_strncmp(pth, ".", 1) != 0)
		pwd = (pth[0] == '/') ? JOIN("PWD=", pth) : join_path(grp, pth);
	else if (!opt && ft_strcmp(pth, "..") == 0)
	{
		cd = ft_strsub(tp, 0, LEN(tp) - (LEN(ft_strrchr(tp, '/')) - 1));
		replce_last_s(&cd[LEN(cd) - 1], LEN(cd));
		pwd = JOIN("PWD=", cd);
		ft_strdel(&cd);
	}
	else if (opt || ft_strncmp(pth, "..", 2) == 0)
		pwd = JOIN("PWD=", getcwd(buf, 1024));
	insert_env(grp, clean_pwd(&pwd));
	insert_env(grp, old_pwd);
	REMOVE(&old_pwd);
	REMOVE(&pwd);
}
