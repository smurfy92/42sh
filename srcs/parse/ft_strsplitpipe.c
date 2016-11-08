#include "fortytwo.h"

static void		insert_part(t_andor **lst, char *cmd)
{
	t_andor		*tmp;
	t_andor		*new;

	new = (t_andor *)malloc(sizeof(t_andor));
	new->cmd = ft_strtrim(cmd);
	ft_strdel(&cmd);
	new->type = 0;
	new->parselst = NULL;
	new->next = NULL;
	if (!*(lst))
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// void			display_lst(t_andor *lst)
// {
// 	t_andor *tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("cmd: %s\n", tmp->cmd);
// 		tmp = tmp->next;
// 	}
// }

t_andor		*ft_strsplitpipe(char *s, char c)
{
	int		i;
	int		start;
	int		synth;
	t_andor	*lst;

	i = -1;
	start = 0;
	lst = NULL;
	while (s[++i] != '\0')
	{
		synth = check_parentheses(s[i]);
		if (synth == 0 && s[i] == c)
		{
			if (i > 0 && s[i - 1] == '\\')
				continue ;
			insert_part(&lst, ft_strsub(s, start, i - start));
			start = i + 2;
			i++;
		}
	}
	insert_part(&lst, ft_strsub(s, start, i - start));
	//display_lst(lst);
	check_parentheses(0);
	return (lst);
}