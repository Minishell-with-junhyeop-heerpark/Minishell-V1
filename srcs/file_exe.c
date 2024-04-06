/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:58 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/06 18:08:57 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_filepath(char **exec_cmd)
{
	if (ft_strncmp(exec_cmd[0], ".", 1) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "~", 1) == 0)
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

void	add_desktoppath(char **exec_cmd)
{
	char	*now_path;
	char	*desktop_path;
	char	*res;
	int		i;

	now_path = get_pwd();
	desktop_path = (char *)malloc(sizeof(char) * 100);
	i = 0;
	while (now_path[i])
	{
		if (now_path[i] == '/')
		{
			if (strncmp(&now_path[i], "/Desktop/", 9) == 0)
				break ;
		}
		i++;
	}
	ft_strlcpy(desktop_path, now_path, i + 1);
	free(now_path);
	res = ft_strjoin(desktop_path, exec_cmd[0] + 1);
	free(exec_cmd[0]);
	free(desktop_path);
	exec_cmd[0] = res;
}
