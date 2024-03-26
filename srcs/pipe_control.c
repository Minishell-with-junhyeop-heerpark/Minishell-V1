/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:13:59 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/26 21:05:14 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_process *process, int **pipes, char **envp, int i)
{
	close(pipes[i][0]);
	dup2(pipes[i][1], STDOUT_FILENO);
	set_inout(process, pipes, i, 1);
	if (is_builtin(process->exec_cmd[0]))
		run_builtin(process->exec_cmd[0], envp);
	else if (execve(process->exec_path, process->exec_cmd, envp) == -1)
		perror_exit("execve error");
}

void	last_child(t_process *process, int **pipes, char **envp, int i)
{
	close(pipes[i - 1][1]);
	dup2(pipes[i - 1][0], STDIN_FILENO);
	set_inout(process, pipes, i, 0);
	if (is_builtin(process->exec_cmd[0]))
		run_builtin(process->exec_cmd[0], envp);
	else if (execve(process->exec_path, process->exec_cmd, envp) == -1)
		perror_exit("execve error");
}

void	mid_child(t_process *process, int **pipes, char **envp, int i)
{
	close(pipes[i][0]);
	close(pipes[i - 1][1]);
	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	set_inout(process, pipes, i, 1);
	if (is_builtin(process->exec_cmd[0]))
		run_builtin(process->exec_cmd[0], envp);
	else if (execve(process->exec_path, process->exec_cmd, envp) == -1)
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

void	wait_process(int child_num)
{
	int	count;
	int	status;
	int	pid;
	int	exit_status;

	count = 0;
	while (count < child_num)
	{
		pid = wait(&status);
		if (pid == -1)
			perror_exit("wait error");
		else if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == EXIT_FAILURE)
			{
				perror_exit("child process exited with error");
			}
		}
		count++;
	}
}
