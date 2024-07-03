/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:50:59 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/03 16:39:43 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process(t_process *process)
{
	if (process->heredoc_filename != NULL)
		free(process->heredoc_filename);
	if (process->cmd != NULL)
		free(process->cmd);
	if (process->exec_path != NULL)
		free(process->exec_path);
	if (process->exec_cmd != NULL)
		free_splited(process->exec_cmd);
}

void	close_fds(t_process *process)
{
	if (process->re_infile_fd > 0)
		close(process->re_infile_fd);
	if (process->re_outfile_fd > 0)
		close(process->re_outfile_fd);
	if (process->re_append_fd > 0)
		close(process->re_append_fd);
	if (process->heredoc_fd > 0)
		close(process->heredoc_fd);
}

void	clear_processes(t_head *head)
{
	t_process	**processes;
	int			i;

	processes = head->processes;
	i = 0;
	while (processes[i])
	{
		free_process(processes[i]);
		close_fds(processes[i]);
		free(processes[i]);
		i++;
	}
	free(processes[i]);
	free(processes);
	if (head->size != 1)
		free_pipe(head->data->pipes, head->size - 1);
}
