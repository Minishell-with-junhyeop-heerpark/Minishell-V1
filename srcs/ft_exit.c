/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:34:06 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/09 10:43:30 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_disit(char *cmd)
{
	int	i;
	int	s;

	s = 0;
	while (cmd[s] == ' ')
		s++;
	i = s;
	if (cmd[i] != '-' && !ft_isdigit(cmd[i]))
		return (0);
	i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]) || i - s > 11)
			return (0);
		i++;
	}
	if (ft_atoi(&cmd[s]) == 0 && cmd[s] != 0)
		return (0);
	return (1);
}

int	ft_exit(char **exec_cmd)
{
	int		num;

	if (exec_cmd[1] == NULL)
	{
		printf("exit\n");
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
		printf("minishell: exit: %s: \
		numeric argument required\n", exec_cmd[1]);
		exit(255);
	}
	printf("exit\n");
	num = 256 + ft_atoi(exec_cmd[1]);
	exit(num % 256);
	return (-1);
}
