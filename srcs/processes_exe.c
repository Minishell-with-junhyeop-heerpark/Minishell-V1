/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:11:25 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 23:34:23 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_inout(t_process *process)
{
	if (process->re_outfile_fd > 0)
	{
		dup2(process->re_outfile_fd, STDOUT_FILENO);
	}
	if (process->re_append_fd > 0)
	{
		dup2(process->re_append_fd, STDOUT_FILENO);
	}
	if (process->re_infile_fd > 0)
	{
		dup2(process->re_infile_fd, STDIN_FILENO);
	}
	if (process->heredoc_fd > 0)
	{
		dup2(process->heredoc_fd, STDIN_FILENO);
	}
}

void	run_cmd(t_head *head, char **envp, int i)
{
	if (is_builtin(head->processes[i]->exec_cmd))
	{
		run_builtin(head, head->processes[i]->exec_cmd);
		exit(g_exit_status);
	}
	if (is_filepath(head->processes[i]->exec_cmd))
	{
		if (execve(head->processes[i]->exec_cmd[0], \
		head->processes[i]->exec_cmd, envp) == -1)
		{
			perror_exit("file exe execve error");
		}
	}
	if (execve(head->processes[i]->exec_path, \
	head->processes[i]->exec_cmd, envp) == -1)
	{
		perror_exit("execve error");
	}
}

void	start_process(t_head *head, char **envp)
{
	pid_t	pid;

	if (is_builtin(head->processes[0]->exec_cmd))
	{
		set_inout(head->processes[0]);
		run_builtin(head, head->processes[0]->exec_cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror_exit("start_process fork error");
	else if (pid == 0)
	{
		temi_print_on();
		set_inout(head->processes[0]);
		run_cmd(head, envp, 0);
	}
}

void	start_processes(t_head *head, char **envp, int **pipes)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < head->size)
	{
		pid = fork();
		if (pid == -1)
			perror_exit("fork error");
		else if (pid == 0)
		{
			temi_print_on();
			if (i == 0)
				first_child(head, pipes, envp, i);
			else if (i == head->size - 1)
				last_child(head, pipes, envp, i);
			else
				mid_child(head, pipes, envp, i);
		}
		else
			parent(pipes, i);
		i++;
	}
}

void	exe(t_head *head, char **envp)
{
	if (head->size == 1)
	{
		get_processes(head, envp);
		if (error_check(head, 0))
			return ;
		start_process(head, envp);
		if (!is_builtin(head->processes[0]->exec_cmd))
			wait_process(head->size);
	}
	else
	{
		head->data->pipes = make_pipe(head->size - 1);
		get_processes(head, envp);
		if (error_check(head, 1))
			return ;
		start_processes(head, envp, head->data->pipes);
		wait_process(head->size);
	}

	set_signal();
}
