/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:00:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/30 15:36:24 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_list_new(char *command)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(0);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->token = make_token(command);
	return (newnode);
}

t_token	*token_new(char *command, int flag, int quote_flag)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_msg(0);
	new->prev = NULL;
	new->next = NULL;
	new->cmd = command;
	new->redir_flag = flag;
	new->quote_flag = quote_flag;
	return (new);
}

t_token	*make_token(char *command)
{
	t_token	*token;

	token = split_space(command, ' ');
	return (token);
}

void	ft_token_add(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = new;
		return ;
	}
	if (tmp == NULL && new == NULL)
		error_msg(0);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	ft_lst_add(t_head *head, t_list *new)
{
	t_list	*tmp;

	head->size += 1;
	tmp = head->top;
	if (tmp == NULL)
	{
		head->top = new;
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
