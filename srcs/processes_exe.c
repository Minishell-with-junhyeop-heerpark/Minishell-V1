/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:11:25 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/27 17:28:32 by junhyeop         ###   ########.fr       */
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
		processes[i] = get_process(head, node, path);
		node = node->next;
		i++;
	}
	processes[i] = NULL;
	free_splited(path);
	head->processes = processes;
	return ;
}

void	 set_inout(t_process *process, int **pipes, int i, int close_sig)
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

// void	start_process(t_head *head, char **envp)
// {
// 	pid_t	pid;

// 	if (is_builtin(head->processes[0]->exec_cmd))
// 	{
// 		set_inout(head->processes[0], NULL, 0, 0);
// 		run_builtin(head, head->processes[0]->exec_cmd);
// 		dup2(head->data->original_stdout, STDOUT_FILENO);
// 		dup2(head->data->original_stdin, STDIN_FILENO);
// 		return ;
// 	}
// 	if (is_filepath(head->processes[0]->exec_cmd))
// 	{
// 		set_inout(head->processes[0], NULL, 0, 0);
// 		if (execve(head->processes[0]->exec_cmd[0], \
// 		head->processes[0]->exec_cmd, envp) == -1)
// 			perror_exit("file exe execve error");
// 		// return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		perror_exit("start_process fork error");
// 	else if (pid == 0)
// 	{
// 		set_inout(head->processes[0], NULL, 0, 0);
// 		if (execve(head->processes[0]->exec_path, \
// 		head->processes[0]->exec_cmd, envp) == -1)
// 			perror_exit("execve error");
// 	}
// }

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
		printf("exe %d!!!!!!\n", i);
		printf("%s\n", head->processes[i]->exec_path);
		printf("%s, %s\n", head->processes[i]->exec_cmd[0], head->processes[i]->exec_cmd[1]);
		printf("%s\n",envp[0]);
		perror_exit("execve error");
	}
}

void	start_process(t_head *head, char **envp) 
{
	pid_t	pid;

	printf("what's up nigger\n");
	if (is_builtin(head->processes[0]->exec_cmd))
	{
		set_inout(head->processes[0], NULL, 0, 0);
		run_builtin(head, head->processes[0]->exec_cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror_exit("start_process fork error");
	else if (pid == 0)
	{
		temi_print_on();
		set_inout(head->processes[0], NULL, 0, 0);
		run_cmd(head, envp, 0);
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
			temi_print_on();
			if (i == 0) 
				first_child(head, pipes, envp, i);
			else if (i == n - 1)
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
	head->get_error = 0;
	if (head->size == 1)
	{
		get_processes(head, envp);
		if (head->get_error)
		{
			set_signal();
			return ;
		}
		start_process(head, envp);
		if (!is_builtin(head->processes[0]->exec_cmd))
			wait_process(head->size);
	}
	else
	{
		head->data->pipes = make_pipe(head->size - 1);
		get_processes(head, envp);
		if (head->get_error)
		{
			set_signal();
			return ;
		}
		start_processes(head, envp, head->data->pipes, head->size);
		wait_process(head->size);
	}
	set_signal();
}
//have to free malloced variable
