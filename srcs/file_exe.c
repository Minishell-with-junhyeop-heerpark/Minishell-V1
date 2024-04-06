/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:58 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/06 17:35:39 by heerpark         ###   ########.fr       */
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

void	add_desktoppath(t_head *head, char **exec_cmd)
{
	char	*res;

	res = ft_strjoin(head->data->home, exec_cmd[0] + 1);
	free(exec_cmd[0]);
	exec_cmd[0] = res;
}
