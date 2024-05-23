/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:07:00 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/23 15:13:09 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	set_env(t_list **head, char **envp)
{
	int		n;
	int		i;
	char	*key;
	char	*value;

	n = 0;
	while (envp[n])
	{
		i = 0;
		while (envp[n][i])
		{
			if (envp[n][i] == '=')
			{
				key = ft_substr(envp[n], 0, i);
				value = ft_substr(envp[n], i + 1, 2147483647);
				lstadd_back(head, lst_new(key, value));
				break ;
			}
			i++;
		}
		n++;
	}
}

char	*get_envp_line(t_list *head)
{
	char	*temp2;
	char	*temp;
	char	*envp;
	t_list	*node;

	node = head;
	envp = ft_strdup("");
	while (node)
	{
		temp = ft_strjoin(node->key, "=");
		temp2 = ft_strjoin(temp, node->value);
		free(temp);
		temp = ft_strjoin(temp2, " ");
		free(temp2);
		temp2 = envp;
		envp = ft_strjoin(envp, temp);
		free(temp2);
		free(temp);
		node = node->next;
	}
	return (envp);
}

void	update_envp(t_head *head)
{
	char	*envp_line;

	envp_line = get_envp_line(head->data->env);
	free_splited(head->data->envp);
	head->data->envp = ft_split(envp_line, ' ');
	free(envp_line);

	for (int i=0; head->data->envp[i]; i++)
	{
		printf("%s\n",head->data->envp[i]);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*head;
// 	char	*envp_line;
// 	char	**my_envp;

// 	set_env(&head, envp);

// 	envp_line = get_envp_line(head);
// 	update_envp()
// }