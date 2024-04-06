/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:11:25 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/06 19:54:45 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_processes(t_head *head, char **envp)
{
	t_process	**processes;
	t_list		*node;
	char		**path;
	int			i;

	processes = (t_process **)malloc(sizeof(t_process *) * (head->size + 1));
	node = head->top;
	path = ft_split(get_envpath(envp), ':');
	if (!path)
		perror_exit("get_processes-split");
	i = 0;
	while (node)
	{
		processes[i] = get_process(node, path);
		node = node->next;
		i++;
	}
	processes[i] = NULL;
	free_splited(path);
	head->processes = processes;
	return ;
}

void	set_inout(t_process *process, int **pipes, int i, int close_sig)
{
	if (process->re_outfile_fd > 0)
	{
		dup2(process->re_outfile_fd, STDOUT_FILENO);
		if (close_sig)
			close(pipes[i][1]);
	}
	if (process->re_append_fd > 0)
	{
		dup2(process->re_append_fd, STDOUT_FILENO);
		if (close_sig)
			close(pipes[i][1]);
	}
	if (process->re_infile_fd > 0)
	{
		dup2(process->re_infile_fd, STDIN_FILENO);
		if (close_sig)
			close(pipes[i][0]);
	}
	if (process->heredoc_fd > 0)
	{
		dup2(process->heredoc_fd, STDIN_FILENO);
		if (close_sig)
			close(pipes[i][0]);
	}
}

void	start_process(t_head *head, char **envp)
{
	pid_t	pid;

	if (is_builtin(head->processes[0]->exec_cmd))
	{
		set_inout(head->processes[0], NULL, 0, 0);
		run_builtin(head, head->processes[0]->exec_cmd);
		dup2(head->data->original_stdout, STDOUT_FILENO);
		dup2(head->data->original_stdin, STDIN_FILENO);
		return ;
	}
	if (is_filepath(head->processes[0]->exec_cmd))
	{
		if (execve(head->processes[0]->exec_cmd[0], \
		head->processes[0]->exec_cmd, envp) == -1)
			perror_exit("file exe execve error");
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror_exit("start_process fork error");
	else if (pid == 0)
	{
		temi_print_on();
		set_inout(head->processes[0], NULL, 0, 0);
		if (execve(head->processes[0]->exec_path, \
		head->processes[0]->exec_cmd, envp) == -1)
			perror_exit("execve error");
	}
}

void	start_processes(t_head *head, char **envp, int **pipes, int n)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < n)
	{
		pid = fork();
		if (pid == -1)
			perror_exit("fork error");
		else if (pid == 0)
		{
			if (i == 0)
				first_child(head, pipes, envp, i);
			else if (i == n - 1)
				last_child(head, pipes, envp, i);
			else
				mid_child(head, pipes, envp, i);
		}
		else
		{
			printf("%d번째 자식 pid: %d\n", i + 1, pid);
			// close_all_pipes(pipes, 1);
			parent(pipes, i);
		}
		i++;
	}
}

void	exe(t_head *head, char **envp)
{
	int			**pipes;

	printf("head size: %d\n", head->size);
	if (head->size < 1)
	{
		// exit(EXIT_FAILURE);
		return ;
	}
	else if (head->size == 1)
	{
		get_processes(head, envp);
		start_process(head, envp);
		if (!is_builtin(head->processes[0]->exec_cmd))
			wait_process(head->size);
	}
	else
	{
		pipes = make_pipe(head->size - 1);
		// close_all_pipes(pipes, head->size - 1);
		get_processes(head, envp);
		start_processes(head, envp, pipes, head->size);
		wait_process(head->size);
	}
	kill_heredoc(head, envp);
	printf("exe end\n");
	set_signal();

	return ;
}
//have to free malloced variable
