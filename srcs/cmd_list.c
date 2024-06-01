/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:00:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 22:36:34 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_list_new(char *command, t_head *head)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(0, NULL);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->token = make_token(command, head);
	return (newnode);
}

t_token	*token_new(char *command, int flag, int quote_flag)
{
	t_token	*new;

	if (!command)
		error_msg(0, NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_msg(0, NULL);
	new->prev = NULL;
	new->next = NULL;
	new->cmd = command;
	new->redir_flag = flag;
	new->quote_flag = quote_flag;
	return (new);
}

t_token	*make_token(char *command, t_head *head)
{
	t_token	*token;

	token = split_space(command, ' ');
	redir_err_check(token, head);
	return (token);
}

void	ft_token_add(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	printf("x : %p\n", tmp);
	printf("new: %s\n", new->cmd);
	if (new == NULL)
		error_msg(0, NULL);
	if (tmp == NULL)
	{
		*lst = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_token	*ft_token_add2(t_token *lst, t_token *new)
{
	t_token	*tmp;

	tmp = lst;
	printf("x : %p\n", tmp);
	printf("new: %s\n", new->cmd);
	if (new == NULL)
		error_msg(0, NULL);
	if (tmp == NULL)
	{
		return (new);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (lst);
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
