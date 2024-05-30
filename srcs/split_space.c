/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/30 14:37:06 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**freeall(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	*split_str(char const *s, char c)
{
	int		n;
	int		i;
	char	*str;

	i = 0;
	n = 0;
	while (*s == ' ')
		s++;
	while (s[n] && s[n] != c)
		n++;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
typedef struct s_make_cmd_var
{
	int	i;
	int	s;
	int	ind;
}	t_make_cmd_var;

char	*make_cmd(char *cmd, t_split_var *sv, char q)
{
	char			*p_cmd;
	t_make_cmd_var	v;

	v = (t_make_cmd_var){set_len(cmd, sv->i, q), sv->start, 0};
	if (v.i - v.s <= 1)
	{
		sv->i = v.i + 1;
		sv->start = v.i + 1;
		return (NULL);
	}
	p_cmd = (char *)malloc(sizeof(char) * (v.i - v.s - 2) + 1);
	if (!p_cmd)
		error_msg(0);
	while (v.s < v.i)
	{
		if (cmd[v.s] != q)
			p_cmd[v.ind++] = cmd[v.s];
		v.s++;
	}
	p_cmd[v.ind] = 0;
	sv->i = v.i + 1;
	sv->start = v.i + 1;
	return (p_cmd);
}

void	split_space_ext(t_split_var *v, char *cmd)
{
	if (cmd[v->i] == '\0')
		v->flag = 1;
	cmd[v->i] = '\0';
	if (v->i > v->start && v->backup)
		v->backup = ft_strjoin(v->backup, &cmd[v->start]);
	if (!v->backup)
		add_token(&v->lst, &cmd[v->start]);
	else
		ft_token_add(&v->lst, token_new(v->backup, 0, v->quote));
	v->backup = NULL;
	v->i++;
	v->start = v->i;
}

t_token	*split_space(char *cmd, char space)
{
	t_split_var	v;

	v = (t_split_var){NULL, NULL, 0, 0, 0, 0, 0};
	while (v.flag == 0 && cmd[v.i])
	{
		v.dquote = 0;
		v.quote = 0;
		while (cmd[v.start] == space)
			v.start++;
		v.i = v.start;
		while (cmd[v.i] != space && cmd[v.i])
		{
			if (s_quote_check(cmd[v.i], &v))
			{
				if (!v.backup)
					v.backup = make_cmd(cmd, &v, cmd[v.i]);
				else
					my_strjoin(&v.backup, make_cmd(cmd, &v, cmd[v.i]));
			}
			else
				v.i++;
		}
		split_space_ext(&v, cmd);
	}
	return (v.lst);
}
