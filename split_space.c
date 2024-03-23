/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/21 22:52:47 by junhyeop         ###   ########.fr       */
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

int	find_redir(char	*cmd)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')

	}
}

void	check_redir(t_list **new)
{
	t_list	*tmp;

	tmp = *new;
	find_redir(tmp->cmd);
}


// redir 기준으로 한번 더 나눔
void	add_token(t_list **lst, char *cmd)
{
	t_list	*tmp;
	int		start;
	int		i;

	i = 0;
	start = 0;
	while (cmd[i])
	{
		if (cmd[start] == '<' || cmd[start] == '>')
			new_token);
	}
}

// input : echo ls >a
// output : echo, ls, >, a

t_token	*split_space(char *s, char space)	// pipe 단위로 나눈 것 -> 공백 단위로 나눔
{
	t_token	*lst;
	int		i;
	int		start;

	i = 0;
	if (!s)
		return (NULL);
	lst = (t_token *)malloc(sizeof(t_token));
	if (!lst)
		return (NULL);
	start = 0;
	while (s[i])
	{
		while (s[start] == space)
			start++;
		i = start;
		while (s[i] != space)
			i++;
		if (s[i] != 0)
			s[i] = '\0';
		add_token(&lst, &s[start]);			// 함수안에서 return 시 lst 위치 확인해보기
		start = i + 1;
		i++;
	}
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