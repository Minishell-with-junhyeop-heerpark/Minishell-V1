/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/02 03:33:27 by junhyeop         ###   ########.fr       */
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
	// sv->start = v.i;
	printf("cmd : %s\n", p_cmd);
	printf("cmd[i] : %c\n", cmd[v.i]);
	return (p_cmd);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return ((char *)str);
}

// void	split_space_ext(t_split_var *v, char *cmd)
// {
// 	char	*tmp;

// 	if (cmd[v->i] == '\0')
// 		v->flag = 1;
// 	cmd[v->i] = '\0';
// 	if (v->i > v->start && v->backup)
// 	{
// 		tmp = v->backup;
// 		v->backup = ft_strjoin2(tmp, &cmd[v->start]);
// 		if (!v->backup)
// 			error_msg(0, NULL);
// 		free(tmp);
// 	}
// 	if (!v->backup)
// 		add_token(&v->lst, &cmd[v->start]);
// 	else
// 		ft_token_add(&v->lst, token_new(ft_strdup(v->backup), 0, v->quote));
// 	free(v->backup);
// 	v->backup = NULL;
// 	v->i++;
// 	v->start = v->i;
// }

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

// void	if_redir_exist(t_split_var *v, char *cmd)
// {
	
// }

void	split_space_ext(t_split_var *v, char *cmd)
{
	int	i;

	i = 0;
	printf("origin backup: %s\n", v->backup);
	printf("----------------cmd[v->i] %c  %d\n",cmd[v->i - v->start], v->i);
	if (cmd[v->i - v->start] == '\0')
		v->flag = 1;
	cmd[v->i - v->start] = '\0';
	// if_redir_exist()
	// while (cmd[i] && !is_redir(cmd[i]) && !is_quote(cmd[i]))
	// 	i++;
	// while (cmd[i] && !is_redir(cmd[i]) && !is_quote(cmd[i]))
	// v->start += i;
	// add_token(&v->lst, ft_strndup(cmd, i));
	// cmd = cmd + i;
	// if (v->i > v->start && v->backup)	// backup이 있었다면 둘이합치기
	// {
	// 	tmp = v->backup;
	// 	v->backup = ft_strjoin(v->backup, &cmd[v->start]);
	// 	free(tmp);
	// 	printf("backup: %s\n", v->backup);
	// }
	if (!v->backup)
	{
		printf("h1\n");
		add_token(&v->lst, ft_strdup(cmd));
	}
	else
	{
		printf("h2\n");
		add_token2(&v->lst, ft_strdup(v->backup), v->quote);
		// v->lst = ft_token_add2(v->lst, token_new(ft_strdup(v->backup), 0, v->quote));
		free(v->backup);
	}
	v->i++;
	v->start = v->i;
	v->backup = NULL;
	free(cmd);
	printf("after: %s\n", v->lst->cmd);
}

t_token	*split_space(char *cmd, char space)
{
	t_split_var	v;
	// char		*tmp;

	v = (t_split_var){NULL, NULL, 0, 0, 0, 0, 0};
	v.dquote = 0;
	v.quote = 0;
	while (v.flag == 0 && cmd[v.i])
	{
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

		if (v.lst)
			printf("before: %s\n", v.lst->cmd);
		printf("start %d\n", v.start);
		split_space_ext(&v, ft_strdup(&cmd[v.start]));
		printf("afffter : %s\n", v.lst->cmd);
	}

	t_token *a = v.lst;
	while (a)
	{
		printf(".... %s %d %d\n", a->cmd, a->redir_flag, a->quote_flag);
		a = a->next;
	}
	printf(".... |\n");

	return (v.lst);
}
