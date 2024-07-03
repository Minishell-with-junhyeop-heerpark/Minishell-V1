/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:13:55 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 16:14:22 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_home(t_head *head)
{
	t_list	*node;
	char	*home;

	node = head->data->env->next;
	while (node)
	{
		if (ft_strncmp(node->key, "HOME", 5) == 0)
		{
			home = ft_strdup(node->value);
			head->data->home = home;
			break ;
		}
		node = node->next;
	}
}

t_head	*init_head(char **envp, int argc, char **argv)
{
	t_head	*head;

	void_argument(argc, argv);
	printf("Welcome to minishell!\n");
	set_signal();
	g_exit_status = 0;
	head = (t_head *)malloc(sizeof(t_head));
	head->data = (t_data *)malloc(sizeof(t_data));
	if (!head)
		error_msg(0, NULL);
	head->get_error = 0;
	head->filtered = (t_list *)malloc(sizeof(t_list));
	head->top = NULL;
	head->data->envp = NULL;
	head->size = 0;
	head->data->original_stdin = dup(STDOUT_FILENO);
	head->data->original_stdout = dup(STDOUT_FILENO);
	head->data->env = (t_list *)malloc(sizeof(t_list));
	head->error_str = NULL;
	set_env(&(head->data->env), envp);
	set_home(head);
	return (head);
}

void	export_update_free(char *env_value, char *value, char *key)
{
	free(env_value);
	free(value);
	free(key);
}

int	key_check(char c)
{
	if (ft_isalpha(c) == 0 && c != '_')
		return (0);
	return (1);
}
