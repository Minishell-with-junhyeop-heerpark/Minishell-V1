/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:13:59 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/27 21:37:28 by heerpark         ###   ########.fr       */
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
	// close(pipes[i][0]);
	dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i], pipes, i, 1);
	run_cmd(head, envp, i);
}

void	last_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i], pipes, i, 0);
	run_cmd(head, envp, i);
}

void	mid_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i], pipes, i, 1);
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

int	make_exit_status(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc >> 8) & 255);
	return ((statloc & 127) + 128);
}

void	wait_process(int child_num)
{
	int	count;
	int	status;
	int	org_status;
	int	pid;

	count = 0;
	while (count < child_num)
	{
		pid = wait(&org_status);
		status = make_exit_status(org_status);
		if (pid == -1)
		{
			perror_exit("wait error");
		}
		else if (WIFSIGNALED(org_status))
		{
			g_exit_status = status;
		}
		else if (WIFEXITED(org_status))
		{
			g_exit_status = WEXITSTATUS(org_status);
		}
		count++;
	}
}

