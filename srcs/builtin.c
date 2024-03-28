/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:29 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/28 19:32:34 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo pwd cd export unset env ex

int	is_builtin(char **exec_cmd)
{
	if (ft_strncmp(exec_cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(exec_cmd[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	run_builtin(char **exec_cmd, char **envp)
{
	if (ft_strncmp(exec_cmd[0], "echo", 5) == 0)
		return ;
	else if (ft_strncmp(exec_cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(exec_cmd[0], "cd", 3) == 0)
		cd(exec_cmd[1]);
	else if (ft_strncmp(exec_cmd[0], "export", 7) == 0)
		return ;
	else if (ft_strncmp(exec_cmd[0], "unset", 6) == 0)
		return ;
	else if (ft_strncmp(exec_cmd[0], "env", 4) == 0)
		env(envp);
	else if (ft_strncmp(exec_cmd[0], "exit", 5) == 0)
		return ;
	else
		printf("it is not built in exec_cmd\n");
	exit(0);
}
