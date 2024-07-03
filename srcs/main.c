/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 16:13:59 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_exit_status;

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
	error_msg(head->get_error + 1, head);
	free_list(head, str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_head	*head;

	// if (ft_strcmp(">>", ">>>") == 0)
	// 	printf("hi\n");
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
			// system("leaks minishell");
			// sleep(2);
			update_envp(head);
			exe(head, head->data->envp);
			clear(head, str);
		}
	}
	return (0);
}
