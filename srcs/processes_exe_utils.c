/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_exe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:47:43 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 11:51:24 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **envp)
{
	char		*env_path;
	char		**path;

	env_path = get_envpath(envp);
	if (env_path == NULL)
		path = NULL;
	else
	{
		path = ft_split(env_path, ':');
		if (!path)
			perror_exit("get_processes-split");
	}
	return (path);
}

void	get_processes(t_head *head, char **envp)
{
	t_process	**processes;
	t_list		*node;
	char		**path;
	int			i;

	processes = (t_process **)malloc(sizeof(t_process *) * (head->size + 1));
	path = get_path(envp);
	i = 0;
	node = head->top;
	while (node)
	{
		processes[i] = get_process(head, node, path);
		node = node->next;
		i++;
	}
	processes[i] = NULL;
	if (path)
		free_splited(path);
	head->processes = processes;
	return ;
}

void	set_inout(t_process *process, int **pipes, int i, int close_sig)
{
	(void)close_sig;
	(void)i;
	(void)pipes;
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
