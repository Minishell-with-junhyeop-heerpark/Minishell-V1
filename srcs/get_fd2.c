/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:22:40 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/02 00:02:24 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile(t_head *head, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		head->get_error = 1;
		printf("minishell: %s: No such file or directory\n", file_name);
	}
	return (fd);
}

int	get_heredoc(t_head *head, t_process *process, char *limiter)
{
	int	fd;

	process->heredoc_filename = get_temp_name();
	printf("!!!!!!!!!heredoc name:%s\n", process->heredoc_filename);
	make_temp(limiter, process->heredoc_filename);
	fd = open(process->heredoc_filename, O_RDONLY);
	if (fd == -1)
	{
		head->get_error = 1;
	}
	return (fd);
}

int	get_outfile(t_head *head, char *file_name)
{
	int	fd;
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		head->get_error = 1;
		printf("minishell: %s: No such file or directory\n", file_name);
	}
	return (fd);
}

int	get_append(t_head *head, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		head->get_error = 1;
		printf("minishell: %s: No such file or directory\n", file_name);
	}
	return (fd);
}
