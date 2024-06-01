/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:34:06 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 19:49:09 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_disit(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] != '-' && !ft_isdigit(cmd[i]))
		return (0);
	i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **exec_cmd)
{
	int		num;

	if (exec_cmd[1] == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (exec_cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		g_exit_status = 1;
		return (1);
	}
	else if (!check_disit(exec_cmd[1]))
	{
		ft_printf("minishell: exit: %s: \
numeric argument required\n", exec_cmd[1]);
		exit(255);
	}
	ft_printf("exit\n");
	num = 256 + ft_atoi(exec_cmd[1]);
	exit(num % 256);
	return (-1);
}
