/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:58 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/09 20:21:14 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_filepath(char **exec_cmd)
{
	if (ft_strncmp(exec_cmd[0], ".", 1) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "/", 1) == 0)
		return (1);
	else
		return (0);
}

char	*get_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (getcwd(cwd, 1024) == NULL)
		perror_exit("get_pwd() error");
	return (cwd);
}

void	add_homepath(t_head *head, char **exec_cmd, int only_home)
{
	char	*res;

	if (only_home)
	{
		free(*exec_cmd);
		*exec_cmd = head->data->home;
	}
	else
	{
		res = ft_strjoin(head->data->home, *exec_cmd + 1);
		free(*exec_cmd);
		*exec_cmd = res;
	}
}
