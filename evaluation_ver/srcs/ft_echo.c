/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:36:54 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 20:15:30 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_option_check(char *cmd)
{
	int	i;

	i = 2;
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "-n", 2) != 0)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **exec_cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (n_option_check(exec_cmd[i]))
	{
		flag = 1;
		i++;
	}
	while (exec_cmd[i])
	{
		printf("%s", exec_cmd[i]);
		i++;
		if (!exec_cmd[i])
			break ;
		printf(" ");
	}
	if (!flag)
		printf("\n");
	g_exit_status = 0;
}
