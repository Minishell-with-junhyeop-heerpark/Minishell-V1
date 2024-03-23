/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/23 22:49:34 by junhyeop         ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return ((size_t)n);
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

int	strcnt(char const *s, char c)
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
				ft_putstr_fd("bash: syntax error near unexpected token `||'", 2);
			n++;
			pipe_flag = 1;
		}
		s++;
	}
	// if (pipe_flag) 마지막에 파이프가 오는 경우!
	// 	input_cmd()
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

// a>b 일때는?

int	is_redir(char cmd)
{
	if (cmd == '<' || cmd == '>')
		return (1);
	return (0);
}

int	check_redir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_redir(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}
// >a, b>c
// redir 기준으로 한번 더 나눔
int	add_token_ext(t_token **lst, char *cmd, int *i, int *s)
{
	if (is_redir(cmd[*i]) && *i > *s)
	{
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 0)); // rediction 이전까지
		*s = *i;
	}
	if (is_redir(cmd[*i]) && *i <= *s)
	{
		while (is_redir(cmd[*i]))									// redir 모두 넘김
			*i += 1;
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 1)); 	// redir 끝날때까지
		*s = *i;
		return (0);
	}
	return (1);
}

void	add_token(t_token **lst, char *cmd)
{
	int		s;
	int		i;
	
	printf(".... %s\n",cmd);
	i = 0;
	s = 0;
	if (!check_redir(cmd))
	{
		ft_token_add(lst, token_new(ft_strdup(cmd), 0));
		return ;
	}
	while (cmd[i])
	{
		if (add_token_ext(lst, cmd, &i, &s))
			i++;
	}
	if (i > s)
		ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0));
}

// input : echo ls >a
// output : echo, ls, >, a

t_token	*split_space(char *command, char space)	// pipe 단위로 나눈 것 -> 공백 단위로 나눔
{
	t_token	*lst;
	int		i;
	int		flag;
	int		start;

	i = 0;
	lst = NULL;
	flag = 0;
	start = 0;
	while (flag == 0 && command[i]) 			// space 기준으로 나눔!
	{
		while (command[start] == space)			// 앞에 공백 지움!
			start++;
		i = start;
		while (command[i] != space && command[i] != '\0')
			i++;
		if (command[i] == '\0')					// 마지막이라면 종료!
			flag = 1;
		command[i] = '\0';						// 분리하기 쉽게 분기지점에 널값을 넣어주었음
		add_token(&lst, &command[start]);			// redir 기준으로 다시 나눔!
		start = i + 1;
		i++;
	}
	t_token *tmp = lst;
	while (tmp)
	{
		printf("%s\n", tmp->cmd);
		tmp = tmp->next;
	}
	printf("|\n");
	return (lst);
}






// int main()
// {
// 	char **str = my_split("sdjkfl | lksadfj | sdklf");
// 	while (*str)
// 	{
// 		printf("%s\n", *str);
// 		str++;
// 	}
// }