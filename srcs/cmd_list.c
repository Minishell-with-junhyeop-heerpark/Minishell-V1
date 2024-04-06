/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:00:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/04/06 22:34:18 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

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

t_head	*init_head(char **envp)
{
	t_head	*head;

	head = (t_head *)malloc(sizeof(t_head));
	head->data = (t_data *)malloc(sizeof(t_data));
	if (!head)
		error_msg(1);
	head->top = NULL;
	head->size = 0;
	head->data->original_stdin = dup(STDOUT_FILENO);
	head->data->original_stdout = dup(STDOUT_FILENO);
	head->data->env = (t_list *)malloc(sizeof(t_list));
	set_env(&(head->data->env), envp);
	set_home(head);
	return (head);
}

// t_token	*init_token()
// {
// 	t_token	*new;

// 	new = (t_token *)malloc(sizeof(t_head));
// 	if (!head)
// 		error_msg(1);
// 	head->top = NULL;
// 	head->size = 0;
// 	return (head);
// }


t_list	*cmd_list_new(char *command)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(1);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->token = make_token(command);
	return (newnode);
}

t_token	*token_new(char *command, int flag, int dquote_flag)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_msg(1);
	new->prev = NULL;
	new->next = NULL;
	new->cmd = command;
	new->redir_flag = flag;
	new->dquote_flag = dquote_flag;
	return (new);
}

t_token	*make_token(char *command)
{
	// int		i;
	t_token	*token;
	
	// i = 0;
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
		error_msg(1) ;
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
