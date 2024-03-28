/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:40:07 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/29 00:35:18 by heerpark         ###   ########.fr       */
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
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			break ;
		before = current;
		current = current->next;
	}
	if (!current)
		return (0);
	if (before == NULL)
		*lst = current->next;
	else
		before->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
	return (0);
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
	while (head)
	{
		printf("%s = %s\n", head->key, head->value);
		head = head->next;
	}
}
