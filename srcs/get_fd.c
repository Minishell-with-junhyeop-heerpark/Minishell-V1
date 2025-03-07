/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:12 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/03 16:07:08 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redir_heredoc(t_process *process)
{
	if (process->re_infile_fd == -1 || process->re_outfile_fd == -1)
		return (-1);
	else if (process->re_append_fd == -1 || process->heredoc_fd == -1)
		return (-1);
	else if (process->re_infile_fd != -42)
		return (1);
	else if (process->re_outfile_fd != -42)
		return (1);
	else if (process->re_append_fd != -42)
		return (1);
	else if (process->heredoc_fd != -42)
		return (1);
	else
		return (0);
}

void	init_fd(t_process *process)
{
	process->re_outfile_fd = -42;
	process->re_append_fd = -42;
	process->re_infile_fd = -42;
	process->heredoc_fd = -42;
}
