/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:43:50 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/24 16:55:13 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envpath(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i];
			break ;
		}
		i++;
	}
	path = path + 5;
	return (path);
}

char	**get_cmd_head(char **argv, int start_idx, int end_idx)
{
	char	**cmds;
	char	**splited_argv;
	int		cmds_count;

	cmds_count = 0;
	cmds = (char **)malloc(sizeof(char *) * (end_idx - start_idx + 2));
	if (!cmds)
		exit (1);
	while (start_idx <= end_idx)
	{
		splited_argv = ft_split(argv[start_idx], ' ');
		if (!splited_argv)
			exit (1);
		cmds[cmds_count++] = splited_argv[0];
		start_idx++;
	}
	cmds[cmds_count] = NULL;
	return (cmds);
}

void	make_path(char ***res, char **path, char **cmds, int count)
{
	int		path_idx;
	char	*now_path;
	char	*exec_path;

	path_idx = 0;
	while (path[path_idx])
	{
		now_path = ft_strjoin(path[path_idx], "/");
		exec_path = ft_strjoin(now_path, cmds[count]);
		free(now_path);
		if (access(exec_path, X_OK) == 0)
		{
			(*res)[count] = exec_path;
			path_idx = -1;
			break ;
		}
		free(exec_path);
		path_idx++;
	}
	if (path_idx != -1)
		perror_exit("command not found");
}

void	find_valid_path(char ***res, char **path, char **cmds, int n)
{
	int		count;

	count = 0;
	while (count < n)
	{
		make_path(res, path, cmds, count);
		count++;
	}
	(*res)[count] = NULL;
}

char	**get_exec_paths(char **envp, char **cmds, int path_size)
{
	char	**path;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (path_size + 1));
	if (!res)
		exit (1);
	path = ft_split(get_envpath(envp), ':');
	if (!path)
		exit (1);
	find_valid_path(&res, path, cmds, path_size);
	free_splited(path);
	return (res);
}
