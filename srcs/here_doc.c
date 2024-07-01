/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:47 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/01 17:40:17 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_temp_name(void)
{
	char	*filename;
	char	*add;
	int		n;

	n = 0;
	while (1)
	{
		add = ft_itoa(n);
		filename = ft_strjoin("temp", add);
		if (access(filename, F_OK) == 0)
		{
			free(add);
			free(filename);
		}
		else
		{
			free(add);
			return (filename);
		}
		n++;
	}
}

char	*my_stradd(char *dest, char *src)
{
	char	*str;
	char	*sstr;

	str = ft_strjoin(dest, src);
	free(dest);
	free(src);
	sstr = ft_strjoin(str, "\n");
	free(str);
	return (sstr);
}

void	get_heredoc_line(char *limiter, int temp_fd)
{
	char	*temp;
	char	*real_temp;

	real_temp = ft_strdup("");
	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
		{
			ft_printf("\033[1A");
			ft_printf("\033[2C");
			break ;
		}
		if (ft_strncmp(temp, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(temp);
			break ;
		}
		real_temp = my_stradd(real_temp, temp);
	}
	write(temp_fd, real_temp, ft_strlen(real_temp) + 1);
	free(real_temp);
}

void	make_infile(char *limiter, char *file_name)
{
	int		temp_fd;

	temp_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		perror_exit("make_infile open error");
	set_signal_heredoc();
	get_heredoc_line(limiter, temp_fd);
	set_signal();
	close(temp_fd);
	exit(0);
}

void	make_temp(char *limiter, char *file_name)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("fork error");
	else if (pid == 0)
		make_infile(limiter, file_name);
	else
		wait_process(1, pid);
}
