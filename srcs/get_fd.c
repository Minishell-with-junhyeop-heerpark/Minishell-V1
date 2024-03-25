/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:29:12 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/24 15:29:50 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(t_process *process)
{
	process->re_outfile_fd = -42;
	process->re_append_fd = -42;
	process->re_infile_fd = -42;
	process->heredoc_fd = -42;
}

int	get_infile(char	*file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror_exit("get_re_in");
	return (fd);
}

int	get_heredoc(t_process *process, char *limiter)
{
	int	fd;

	process->heredoc_filename = make_infile(limiter);
	fd = open(process->heredoc_filename, O_RDONLY);
	if (fd == -1)
		perror_exit("get_heredoc");
	return (fd);
}

int	get_outfile(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("get_re_out");
	return (fd);
}

int	get_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		perror_exit("get_append");
	return (fd);
}
