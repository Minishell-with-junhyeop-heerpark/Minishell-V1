/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:13:59 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/11 21:13:41 by junhyeop         ###   ########.fr       */
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
	if (is_builtin(head->processes[i]->exec_cmd))
	{
		run_builtin(head, head->processes[i]->exec_cmd);
		exit(0);
	}
	if (is_filepath(head->processes[i]->exec_cmd))
	{
		if (execve(head->processes[i]->exec_cmd[0], \
		head->processes[i]->exec_cmd, envp) == -1)
			perror_exit("file exe execve error");
		return ;
	}
	if (execve(head->processes[i]->exec_path, \
	head->processes[i]->exec_cmd, envp) == -1)
		perror_exit("execve error");
}

void	last_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i], pipes, i, 0);
	if (is_builtin(head->processes[i]->exec_cmd))
	{
		run_builtin(head, head->processes[i]->exec_cmd);
		exit(0);
	}
	if (is_filepath(head->processes[i]->exec_cmd))
	{
		if (execve(head->processes[i]->exec_cmd[0], \
		head->processes[i]->exec_cmd, envp) == -1)
			perror_exit("file exe execve error");
		return ;
	}
	if (execve(head->processes[i]->exec_path, \
	head->processes[i]->exec_cmd, envp) == -1)
		perror_exit("execve error");
}

void	mid_child(t_head *head, int **pipes, char **envp, int i)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, head->size - 1);
	set_inout(head->processes[i], pipes, i, 1);
	if (is_builtin(head->processes[i]->exec_cmd))
	{
		run_builtin(head, head->processes[i]->exec_cmd);
		exit(0);
	}
	if (is_filepath(head->processes[i]->exec_cmd))
	{
		if (execve(head->processes[i]->exec_cmd[0], \
		head->processes[i]->exec_cmd, envp) == -1)
			perror_exit("file exe execve error");
		return ;
	}
	if (execve(head->processes[i]->exec_path, \
	head->processes[i]->exec_cmd, envp) == -1)
		perror_exit("execve error");
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
	int	pid;

	count = 0;
	while (count < child_num)
	{
		pid = wait(&status);
		printf("\n\nbefore status: %d\n\n", status);
		status = make_exit_status(status);
		printf("\n\nprocess end: %d\n", pid);
		printf("after status:  %d\n\n",status);
		printf("wifsig : %d\n\n", WIFSIGNALED(status));
		if (pid == -1)
		{
			perror_exit("wait error");
		}
		else if (WIFSIGNALED(status))
		{
			g_exit_status = status;
			printf("g_exit_status error code %d\n", g_exit_status);
		}
		else if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
			printf("error code %d\n", g_exit_status);
		}
		count++;
	}
	printf("wait end\n");
}

