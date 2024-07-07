/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:43:50 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/07 18:15:12 by junhyeong        ###   ########.fr       */
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
			path = path + 5;
			return (path);
			break ;
		}
		i++;
	}
	return (NULL);
}

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
