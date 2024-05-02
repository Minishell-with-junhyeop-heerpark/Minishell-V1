/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:29 by junhyeop          #+#    #+#             */
/*   Updated: 2024/04/28 22:29:15 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char c, t_flag *flag)
{
	if (flag->dquote == 1)					// "의 안이라면 넘어감
		return (flag->quote);
	if (c == '\'' && flag->quote == 0)	// ' 시작
		return (1);
	if ((c == '\'') && flag->quote == 1)	// ' 끝남
		return (0);
	return (flag->quote);
}

int	dquote_check(char c, t_flag *flag)
{
	if (flag->quote == 1)
		return (flag->dquote);
	if (c == '\"' && flag->dquote == 0)
		return (1);
	if ((c == '\"') && flag->dquote == 1)
		return (0);
	return (flag->dquote);
}

int	is_empty(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	add_cmd(t_head *head, char *line, int pipe_flag)
{
	int		i;
	char	*command;

	(void)pipe_flag;
	i = 0;
	if (line[i] == ' ')
		i++;
	command = ft_strdup(&line[i]);
	if (!command)
		error_msg(1);
	if (is_empty(command))
	{
		
	}
	ft_lst_add(head, cmd_list_new(command));
	free(command);
}

void	parse(char *line, t_head *head)
{
	t_flag	flag;
	int		start;
	int		i;

	flag = (t_flag){0, 0, 1};
	i = 0;
	start = 0;
	while (1)
	{
		// echo '"asdfsdf" | cat'
		flag.quote = quote_check(line[i], &flag);	// quote 여부 확인
		flag.dquote = dquote_check(line[i], &flag); // dquote 여부 확인
		// 분기해야할 때 quote 확인
		if (line[i] == '\0' || (line[i] == '|' && (flag.quote == 0 && flag.dquote == 0)))
		{
			if (line[i] == '\0')
				flag.pipe = 0;	// 끝난 부분이 pipe가 아니라면
			line[i] = '\0';		// 분리하기 쉽게 널 값으로 변환
			// printf("confirm %s\n", &line[start]);
			add_cmd(head, &line[start], flag.pipe);
			start = i + 1;
			if (flag.pipe == 0)
				break ;
		}
		i++;
	}
}

// int	error_check(char *str)
// {
// 	int n;
// 	char *command;

// 	n = 0;
// 	while (str[n] != ' ' || str[n] != ';' || str[n] != '|')
// 		n++;
// 	command = (char *)malloc(sizeof(char) * n + 1);
// 	command = memcpy(command, str, n);
// 	printf("%s", command);
// 	split_pipe(str);
// 	return (1);
// }

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	while (*envp != NULL)
// 	{
// 		printf("%s\n", *envp);
// 		envp++;
// 	}

// 	error_check("asdhfjkl sdfsdkf | dsfjklds");
// 	return (0);
// }