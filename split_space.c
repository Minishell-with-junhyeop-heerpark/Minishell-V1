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

t_list	*split_space(char *s, char space)
{
	t_list	*lst;
	int		i;
	int		start;

	i = 0;
	if (!s)
		return (NULL);
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	start = 0;
	while (s[i])
	{
		while (s[i] && s[i] == space)
			i++;
		start = i; 
		while (*s != space)
			i++;
		if (s[i] != 0)
			s[i] = '\0';
		add_list()
		while (*s && *s != space)
			s++;
	}
	strs[i] = 0;     
	return (strs);
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