/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:11:25 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/28 20:16:52 by heerpark         ###   ########.fr       */
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

void	start_process(t_process **pss, char **envp)
{
	pid_t	pid;

	if (ft_strncmp(pss[0]->exec_cmd[0], "cd", 3) == 0)
	{
		printf("zz\n");
		cd(pss[0]->exec_cmd[1]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror_exit("start_process fork error");
	else if (pid == 0)
	{
		set_inout(pss[0], NULL, 0, 0);
		if (is_builtin(pss[0]->exec_cmd))
			run_builtin(pss[0]->exec_cmd, envp);
		else if (execve(pss[0]->exec_path, pss[0]->exec_cmd, envp) == -1)
			perror_exit("execve error");
	}
}

void	start_processes(t_process **pss, char **envp, int **pipes, int n)
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
				first_child(pss[i], pipes, envp, i);
			else if (i == n - 1)
				last_child(pss[i], pipes, envp, i);
			else
				mid_child(pss[i], pipes, envp, i);
		}
		else
			parent(pipes, i);
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
		start_process(head->processes, envp);
		if (ft_strncmp(head->processes[0]->exec_cmd[0], "cd", 3) != 0)
			wait_process(head->size);
	}
	else
	{
		pipes = make_pipe(head->size - 1);
		get_processes(head, envp);
		start_processes(head->processes, envp, pipes, head->size);
		wait_process(head->size);
	}
	kill_heredoc(head, envp);
	printf("exe end\n");
	return ;
}
//have to free malloced variable
