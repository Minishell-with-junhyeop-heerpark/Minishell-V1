/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:29 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/06 18:58:57 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo pwd cd export unset env exit

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

void	run_builtin(t_head *head, char **exec_cmd) //env 내가만든 env로 대체
{
	// printf("%s\n" ,(exec_cmd[0]));
	if (ft_strncmp(exec_cmd[0], "echo", 5) == 0)
		ft_echo(exec_cmd) ;
	else if (ft_strncmp(exec_cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(exec_cmd[0], "cd", 3) == 0)
		cd(exec_cmd[1]);
	else if (ft_strncmp(exec_cmd[0], "export", 7) == 0)
		return ;
	else if (ft_strncmp(exec_cmd[0], "unset", 6) == 0)
		unset(head, exec_cmd[1]);
	else if (ft_strncmp(exec_cmd[0], "env", 4) == 0)
		env(head);
	else if (ft_strncmp(exec_cmd[0], "exit", 5) == 0)
		return ;
	else
		printf("it is not built in exec_cmd\n");
	// exit(0);
}
