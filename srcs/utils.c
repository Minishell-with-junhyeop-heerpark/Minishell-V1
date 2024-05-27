/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:17:19 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 19:36:10 by heerpark         ###   ########.fr       */
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
		free(rmv->cmd);
		free(rmv);
	}
}

void	free_list(t_head *head, char *str)
{
	t_list	*tmp;
	t_list	*rmv;

	free(str);
	tmp = head->top;
	while (tmp)
	{
		rmv = tmp;
		tmp = tmp->next;
		free_token(rmv->token);
		free(rmv);
	}
	clear_processes(head);
	head->size = 0;
	head->top = NULL;
	head->get_error = 0;
}
