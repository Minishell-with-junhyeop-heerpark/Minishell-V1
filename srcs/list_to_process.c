/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:47 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 15:03:38 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin(t_head *head, t_process *process, char **exec_cmd)
{
	if (exec_cmd[1] && ft_strncmp(exec_cmd[1], "~", 1) == 0)
	{
		if (ft_strncmp(exec_cmd[1], "~/", 2) == 0)
			add_homepath(head, &exec_cmd[1], 0);
		else
			add_homepath(head, &exec_cmd[1], 1);
	}
	process->exec_path = NULL;
	return ;
}

void	check_path(t_process *process, char **path, char **exec_path, int *i)
{
	char	*test_path;

	if (path)
	{
		while (path[*i])
		{
			test_path = ft_strjoin(path[*i], "/");
			*exec_path = ft_strjoin(test_path, process->exec_cmd[0]);
			if (access(*exec_path, X_OK) == 0)
			{
				*i = -1;
				free(test_path);
				break ;
			}
			free(test_path);
			free(*exec_path);
			(*i)++;
		}
	}
}

void	set_exec(t_head *head, t_process *process, char **path, int i)
{
	char	*exec_path;

	check_path(process, path, &exec_path, &i);
	if (path == NULL || i != -1)
	{
		exec_path = NULL;
		print_bash_error(process->exec_cmd[0], "command not found", 127);
		head->get_error = 1;
		if (process->heredoc_fd != -42)
			unlink(process->heredoc_filename);
	}
	process->exec_path = exec_path;
}

void	set_process(t_head *head, t_process *process, char **path)
{
	char	**exec_cmd;

	exec_cmd = ft_split(process->cmd, '\n');
	process->exec_cmd = exec_cmd;
	if (no_cmd(head, process))
		return ;
	if (is_builtin(exec_cmd))
		set_builtin(head, process, exec_cmd);
	else if (is_filepath(exec_cmd))
	{
		if (ft_strncmp(exec_cmd[0], "~", 1) == 0)
			add_homepath(head, &exec_cmd[0], 0);
		process->exec_path = NULL;
	}
	else
	{
		set_exec(head, process, path, 0);
	}
}

void	init_process(t_process *process)
{
	process->heredoc_filename = NULL;
	process->cmd = NULL;
	process->exec_cmd = NULL;
	process->exec_cmd = NULL;
}

t_process	*get_process(t_head *head, t_list *line, char **path)
{
	t_process	*process;
	t_token		*temp;
	char		*cmd;

	process = (t_process *)malloc(sizeof(t_process));
	init_process(process);
	process->env = head->data->env;
	cmd = ft_strdup("");
	temp = line->token;
	init_fd(process);
	fill_elem(head, temp, process, &cmd);
	process->cmd = cmd;
	set_process(head, process, path);
	return (process);
}
