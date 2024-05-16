/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:40:07 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/16 14:15:32 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*lst_new(char *key, char *value)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

char	*remove_node(t_list **lst, char *key)
{
	t_list	*before;
	t_list	*current;

	current = *lst;
	before = NULL;
	printf("remove node\n");
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			printf("found: %s\n", current->key);
			break ;
		}
		before = current;
		current = current->next;
	}
	if (!current)
		return (0);
	if (before == NULL)
		*lst = current->next;
	else
		before->next = current->next;
	printf("%s\n", before->key);
	printf("%s\n", current->next->key);
	printf("------------remove end------------\n");
	free(current->key);
	free(current->value);
	free(current);
	return (0);
}

void	get_node_value(t_list *env, t_token *token)
{
	t_list	*temp;
	char	*res;

	temp = env->next;
	while (temp)
	{
		if (ft_strncmp(temp->key, (token->cmd + 1), \
		ft_strlen(temp->key) + 1) == 0)
		{
			res = ft_strdup(temp->value);
			free(token->cmd);
			token->cmd = res;
			return ;
		}
		temp = temp->next;
	}
	free(token->cmd);
	token->cmd = ft_strdup("");
}

void	lst_clear(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	lst_print(t_list *head)
{
	printf("lst print\n");
	while (head)
	{
		ft_printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
