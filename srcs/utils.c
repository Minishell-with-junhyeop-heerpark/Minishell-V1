/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:17:19 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 19:21:23 by junhyeop         ###   ########.fr       */
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

void	free_filterd(t_head *head)
{
	t_token	*tmp;
	t_token *rmv;

	tmp = head->filtered->token;
	while (tmp)
	{
		rmv = tmp;
		tmp = tmp->next;
		if (rmv->cmd)
			free(rmv->cmd);
		free(rmv);
	}
	head->filtered->token = NULL;
}

void	free_list(t_head *head, char *str)
{
	t_list	*tmp;
	t_list	*rmv;

	tmp = head->top;
	free_filterd(head);
	while (tmp)
	{
		rmv = tmp;
		tmp = tmp->next;
		free_token(rmv->token);
		free(rmv);
	}
	if (head->processes)
		clear_processes(head);
	if (head->error_str)		
		free(head->error_str);
	head->error_str = NULL;
	head->size = 0;
	head->top = NULL;
	head->get_error = 0;
	head->processes = NULL;
	free(str);
}

void	clear(t_head *head, char *str)
{
	kill_heredoc(head);
	free_list(head, str);
}
