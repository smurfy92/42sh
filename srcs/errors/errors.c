
#include "fortytwo.h"

void	error_cmd(char *what, char *who)
{
	prompt();
	ft_putstr_fd(what, 2);
	ft_putstr_fd(" -> ", 2);
	ft_putendl_fd(who, 2);
}

int		error_env_opt(char opt, char *what)
{
	ft_putstr_fd("env:", 2);
	ft_putstr_fd(what, 2);
	ft_putendl_fd(&opt, 2);
	ft_putendl_fd(
"usage: env [-i] [name=value] [utility [argument]", 2);
	return (-1);
}