/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 06:30:07 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/25 16:40:00 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(int type)
{
	if (type == 1)
		ft_putstr_fd("malloc error\n", 2);
	if (type == 2)
	{
		ft_putstr_fd("minishell: Command not found\n", 2);
		g_exit_status = 127;
		return ;
	}
	exit(1);
}