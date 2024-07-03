/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:30:07 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 14:28:54 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(int type)
{
	if (type == 0)
		ft_putstr_fd("malloc error\n", 2);
	if (type == 2)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_exit_status = 127;
		return ;
	}
	if (type == 3 || type == 4 || type == 5)
	{
		if (type == 3)
			ft_putstr_fd \
			("minishell: syntax error near unexpected token `|'\n", 2);
		if (type == 4)
			ft_putstr_fd("minishell: syntax error for unclosed token\n", 2);
		if (type == 5)
			ft_putstr_fd \
			("minishell: syntax error near unexpected token `||'\n", 2);
		g_exit_status = 258;
		return ;
	}
	exit(1);
}

void	print_error(char *cmd, char *input, char *msg, int exit_status)
{
	if (input == NULL)
		ft_printf("%s: %s: %s\n", cmd, "", msg);
	else
		ft_printf("%s: %s: %s\n", cmd, input, msg);
	g_exit_status = exit_status;
}

void	print_bash_error(char *input, char *msg, int exit_status)
{
	if (input == NULL)
		printf("minishell: %s: %s\n", "", msg);
	else
		printf("minishell: %s: %s\n", input, msg);
	g_exit_status = exit_status;
}

int	error_check(t_head *head, int close_pipes)
{
	if (head->get_error)
	{
		set_signal();
		if (close_pipes)
			close_all_pipes(head->data->pipes, head->size - 1);
		return (1);
	}
	return (0);
}
