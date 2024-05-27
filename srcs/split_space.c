/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/25 21:05:17 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

char	**freeall(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

int	strcnt(char const *s, char c, t_head *head)
{
	int	n;
	int	pipe_flag;

	pipe_flag = 0;
	n = 0;
	while (*s)
	{
		if (*s != ' ' && *s != c)
			pipe_flag = 0;
		if (*s == c)
		{
			if (pipe_flag == 1)
			{
				printf("here\n");
				head->get_error = 2;
			}
			n++;
			pipe_flag = 1;
		}
		s++;
	}
	return (n + 1);
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

int	s_quote_check(char c, t_split_var *flag)
{
	if (c == '\'')
	{
		flag->quote = 1;
		flag->dquote = 0;
	}
	else if (c == '\"')
	{
		flag->quote = 0;
		flag->dquote = 1;
	}
	else
		return (0);
	return (1);
}

int	s_dquote_check(char c, t_split_var *flag)
{
	if (flag->dquote == 1)
		return (1);
	if (c == '\"' && flag->dquote == 0)
	{
		flag->dquote = 1;
		return (1);
	}
	if ((c == '\"') && flag->dquote == 1)
	{
		flag->dquote = 0;
		return (0);
	}
	return (flag->dquote);
}

int	set_len(char *str, int i, char q)
{
	i++;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (-1);
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
		head->get_error = 1;
	if (i - s <= 1)
	{
		v->i = i + 1;
		v->start = i + 1;
		return (NULL);
	}
	ind = 0;
	p_cmd = (char *)malloc(sizeof(char) * (i - s - 2) + 1);
	if (!p_cmd)
		error_msg(1);
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
		}
		split_space_ext(&v, cmd);
	}
	return (v.lst);
}
