/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 17:25:56 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gcc testsignal.c -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include

int	check_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	void_argument(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	parse_error(char *str, t_head *head)
{
	error_msg(head->get_error + 1);
	free_list(head, str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_head	*head;

	head = init_head(envp, argc, argv);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			exit_signal();
		else if (*str == '\0' || check_white_space(str))
			free(str);
		else
		{
			add_history(str);
			if (parse(str, head) == 0)
			{
				parse_error(str, head);
				continue ;
			}
			exe(head, envp);
			kill_heredoc(head);
			free_list(head, str);
		}
	}
	return (0);
}
