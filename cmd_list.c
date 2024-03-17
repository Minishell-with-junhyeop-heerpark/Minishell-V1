/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:22:43 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/17 07:55:34 by junhyeop         ###   ########.fr       */
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

t_list	*ft_lstnew(char *cmd)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(1);
	newnode->next = NULL;
	newnode->cmd = cmd;
	return (newnode);
}