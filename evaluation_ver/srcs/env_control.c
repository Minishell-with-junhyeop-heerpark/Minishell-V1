/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:07:00 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/31 21:21:15 by heerpark         ###   ########.fr       */
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
		if (node->value != NULL)
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

	envp_line = get_envp_line(head->data->env->next);
	if (head->data->envp != NULL)
		free_splited(head->data->envp);
	head->data->envp = ft_split(envp_line, ' ');
	free(envp_line);
}
