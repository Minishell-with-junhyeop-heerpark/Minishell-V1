/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:29 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/17 08:25:32 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char c, int quote_flag)
{
	if ((c == '\'' || c == '\"') && quote_flag == 0)
		return (1);
	else if ((c == '\'' || c == '\"') && quote_flag == 1)
		return (0);
}

void	add_cmd(t_head *head, char *line, int pipe_flag)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		error_msg(1);
	new->next = head->top;
	head->top = new;
	new->cmd = cmd_split(line, ' ');
	if (!new->cmd)
		error_msg(1);
	
}

void	parse(char *line, t_head *head)
{
	t_falg	flag;
	int		s_ind;
	int		i;

	flag = (t_falg){0, 0, 1};
	i = 0;
	s_ind = 0;
	while (1)
	{
		flag.quote = quote_check(line[i], flag.quote);
		if (line[i] == '\0' || (line[i] == '|' && flag.quote == 0))
		{
			if (line[i] == '\0')
				flag.pipe = 0;
			line[i] = '\0';
			
			add_cmd(head, &line[s_ind], flag.pipe);
			
			s_ind = i + 1;
			if (flag.pipe == 0)
				break ;
		}
		i++;
	}
}

int	error_check(char *str)
{
	int n;
	char *command;

	n = 0;
	while (str[n] != ' ' || str[n] != ';' || str[n] != '|')
		n++;
	command = (char *)malloc(sizeof(char) * n + 1);
	command = memcpy(command, str, n);
	printf("%s", command);
	// ft_split()
	return (1);
}

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