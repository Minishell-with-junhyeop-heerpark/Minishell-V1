/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:47 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/23 22:48:33 by heerpark         ###   ########.fr       */
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
			return (filename);
		n++;
	}
}

char	*my_stradd(char *dest, char *src)
{
	int		i;
	char	*str;
	char	*sstr;

	i = 0;
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
		wait_process(1);
}

void	set_rm_path(t_head *head, char **envp)
{
	int		path_idx;
	char	**path;
	char	*now_path;
	char	*exec_path;

	path = ft_split(get_envpath(envp), ':');
	path_idx = 0;
	while (path[path_idx])
	{
		now_path = ft_strjoin(path[path_idx], "/");
		exec_path = ft_strjoin(now_path, "rm");
		free(now_path);
		if (access(exec_path, X_OK) == 0)
		{
			head->exec_rm_path = exec_path;
			path_idx = -1;
			break ;
		}
		free(exec_path);
		path_idx++;
	}
	free_splited(path);
	if (path_idx != -1)
		perror_exit("rm not found");
}

void	set_rm_cmd(t_head *head, char *filename)
{
	char	*temp;
	char	*file_cwd;
	char	*cmd;
	char	*cwd;
	char	buf[1024];

	cwd = getcwd(buf, sizeof(buf));
	if (cwd == NULL) 
		perror_exit("getcwd() error");
	temp = ft_strjoin("/", filename);
	file_cwd = ft_strjoin(cwd, temp);
	free(temp);
	cmd = ft_strjoin("rm ", file_cwd);
	free(file_cwd);
	head->exec_rm_cmd = ft_split(cmd, ' ');
	free(cmd);
}

//delete the heredoc temporay file and free the var heredoc_name
void	kill_heredoc(t_head *head, char **envp)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (head->processes[i])
	{
		if (head->processes[i]->heredoc_fd > 0)
		{
			set_rm_path(head, envp);
			set_rm_cmd(head, head->processes[i]->heredoc_filename);
			pid = fork();
			if (pid == -1)
				perror_exit("kill_heredoc fork error");
			else if (pid == 0)
			{
				if (execve(head->exec_rm_path, head->exec_rm_cmd, envp) == -1)
					perror_exit("execve error");
			}
			else
				wait_process(1);
			break ;
		}
		i++;
	}
}
