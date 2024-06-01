/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 15:44:09 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_process(t_process *process)
{
	process->heredoc_filename = NULL;
	process->cmd = NULL;
	process->exec_cmd = NULL;
	process->exec_cmd = NULL;
}

int	get_redir_flag(char	*token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strncmp(token, ">", 2) == 0)
			return (1);
		else if (ft_strncmp(token, "<", 2) == 0)
			return (3);
	}
	else if (ft_strlen(token) == 2)
	{
		if (ft_strncmp(token, ">>", 3) == 0)
			return (2);
		else if (ft_strncmp(token, "<<", 3) == 0)
			return (4);
	}
	return (0);
}

void	close_unused_input(t_process *process)
{
	if (process->heredoc_fd != -42)
	{
		if (process->heredoc_fd != -1)
		{
			close(process->heredoc_fd);
			unlink(process->heredoc_filename);
			free(process->heredoc_filename);
		}
		process->heredoc_fd = -42;
	}
	if (process->re_infile_fd != -42)
	{
		if (process->re_infile_fd != -1)
		{
			close(process->re_infile_fd);
		}
		process->re_infile_fd = -42;
	}
}

void	close_unused_output(t_process *process)
{
	if (process->re_append_fd != -42)
	{
		if (process->re_append_fd != -1)
			close(process->re_append_fd);
		process->re_append_fd = -42;
	}
	if (process->re_outfile_fd != -42)
	{
		if (process->re_outfile_fd != -1)
			close(process->re_outfile_fd);
		process->re_outfile_fd = -42;
	}
}

void	set_fd(t_head *head, t_process *process, \
		char *file_name, int redir_flag)
{
	if (redir_flag == 1)
	{
		close_unused_output(process);
		process->re_outfile_fd = get_outfile(head, file_name);
	}
	else if (redir_flag == 2)
	{
		close_unused_output(process);
		process->re_append_fd = get_append(head, file_name);
	}
	else if (redir_flag == 3)
	{
		close_unused_input(process);
		process->re_infile_fd = get_infile(head, file_name);
	}
	else if (redir_flag == 4)
	{
		close_unused_input(process);
		process->heredoc_fd = get_heredoc(head, process, file_name);
	}
}
