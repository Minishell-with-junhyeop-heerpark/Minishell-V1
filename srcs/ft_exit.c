/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:34:06 by junhyeop          #+#    #+#             */
/*   Updated: 2024/04/10 14:45:52 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_disit(char *cmd) {
	int	i;

	i = 0;
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
	int	num;
	if (exec_cmd[1] == NULL)	// If exit no arguments
		exit(0);
		
	// if exit argument is exist
	if (exec_cmd[2] != NULL)	// If exit arguments more than one 
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (1);
	}
	else if (!check_disit(exec_cmd[1]))	// If exit argument is not disit
	{
		printf("minishell: exit: %s: numeric argument required\n", exec_cmd[1]);
		return (255);
	}

	num = ft_atoi(exec_cmd[1]);
	exit(num % 256);
	return (-1);
}
