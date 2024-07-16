/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/07 18:07:28 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	p_cmd = (char *)malloc(sizeof(char) * (v.i - v.s) + 1);
	if (!p_cmd)
		error_msg(0, NULL);
	while (v.s < v.i)
	{
		p_cmd[v.ind++] = cmd[v.s];
		v.s++;
	}
	p_cmd[v.ind] = 0;
	sv->i = v.i;
	return (p_cmd);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

t_token	*split_space(char *cmd, char space)
{
	t_split_var	v;

	v = (t_split_var){NULL, NULL, 0, 0, 0, 0, 0};
	v.dquote = 0;
	v.quote = 0;
	while (v.flag == 0 && cmd[v.i])
	{
		while (cmd[v.start] == space)
			v.start++;
		v.i = v.start;
		while ((v.dquote || v.quote || cmd[v.i] != space) && cmd[v.i])
		{
			my_quote_check(cmd[v.i], &v.quote, &v.dquote);
			v.i++;
		}
		add_token(&v.lst, ft_strndup(&cmd[v.start], v.i - v.start));
		v.start = v.i;
	}
	return (v.lst);
}
