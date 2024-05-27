/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:17:19 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 20:56:42 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_token	*rmv;

	while (token)
	{
		rmv = token;
		token = token->next;
		if (rmv->cmd)
			free(rmv->cmd);
		free(rmv);
	}
}

void	free_list(t_head *head, char *str)
{
	t_list	*tmp;
	t_list	*rmv;

	tmp = head->top;
	while (tmp)
	{
		rmv = tmp;
		tmp = tmp->next;
		free_token(rmv->token);
		free(rmv);
	}
	if (head->processes)
		clear_processes(head);
	head->size = 0;
	head->top = NULL;
	head->get_error = 0;
	head->processes = NULL;
	free(str);
}
