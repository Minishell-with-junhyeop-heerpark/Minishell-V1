/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 21:17:47 by junhyeop         ###   ########.fr       */
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

char	*make_cmd(t_head *head, char *cmd, t_split_var *v, char q)
{
	char	*p_cmd;
	int		i;
	int		s;
	int		ind;

	s = v->start;
	i = set_len(cmd, v->i, q);
	if (i == -1)
	{
		head->get_error = 1;
		return (NULL);
	}
	if (i - s <= 1)
	{
		v->i = i + 1;
		v->start = i + 1;
		return (NULL);
	}
	ind = 0;
	p_cmd = (char *)malloc(sizeof(char) * (i - s - 2) + 1);
	if (!p_cmd)
		error_msg(0);
	while (s < i)
	{
		if (cmd[s] != q)
			p_cmd[ind++] = cmd[s];
		s++;
	}
	p_cmd[ind] = 0;
	v->i = i + 1;
	v->start = i + 1;
	return (p_cmd);
}

void	split_space_ext(t_split_var *v, char *cmd)
{
	if (cmd[v->i] == '\0')
		v->flag = 1;
	cmd[v->i] = '\0';
	if (v->i > v->start && v->backup)	// backup이 있었다면 둘이합치기
		v->backup = ft_strjoin(v->backup, &cmd[v->start]);
	if (!v->backup)
		add_token(&v->lst, &cmd[v->start]);
	else
		ft_token_add(&v->lst, token_new(v->backup, 0, v->quote));
	v->backup = NULL;
	v->i++;
	v->start = v->i;
}

t_token	*split_space(t_head *head, char *cmd, char space)
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
					v.backup = make_cmd(head, cmd, &v, cmd[v.i]);
				else
					my_strjoin(&v.backup, make_cmd(head, cmd, &v, cmd[v.i]));
			}
			else
				v.i++;
			if (head->get_error)
				return (NULL);
		}
		split_space_ext(&v, cmd);
	}
	return (v.lst);
}
