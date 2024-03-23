/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:22:43 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/21 22:40:54 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_head	*list_init()
{
	t_head	*head;

	head = (t_head *)malloc(sizeof(t_head));
	if (!head)
		error_msg(1);
	head->top = NULL;
	head->size = 0;
	return (head);
}


t_list	*cmd_list_new(char *command)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(1);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->cmd = make_token(command);
	return (newnode);
}

t_token	*token_list_new(char *command)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_msg(1);
	new->prev = NULL;
	new->next = NULL;
	new->redir_flag = 0;
	new->cmd = command;
}

t_token	*make_token(char *command)
{
	int		i;
	t_token	*token;
	
	i = 0;
	token = space_split(command);
	
}

void	ft_lstadd_back(t_head *head, t_list *new)
{
	t_list	*tmp;

	tmp = head->top;
	if (tmp == NULL)
	{
		tmp = new;
		return ; 
	}
	else if (tmp == NULL && new == NULL)
		return ;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
