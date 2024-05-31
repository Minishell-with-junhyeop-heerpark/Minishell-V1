/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:25:36 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/31 21:26:14 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_heredoc(t_head *head)
{
	int		i;

	i = 0;
	while (head->processes[i])
	{
		if (head->processes[i]->heredoc_fd > 0)
		{
			unlink(head->processes[i]->heredoc_filename);
		}
		i++;
	}
}
