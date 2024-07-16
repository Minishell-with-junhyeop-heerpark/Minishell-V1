/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:13:59 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/07 18:17:19 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	first_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i]);
	run_cmd(head, envp, i);
}

void	last_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i]);
	run_cmd(head, envp, i);
}

void	mid_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i]);
	run_cmd(head, envp, i);
}

void	parent(int **pipes, int i)
{
	if (i > 0)
	{
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
	}
}
