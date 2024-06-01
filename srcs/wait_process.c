/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:45:11 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 11:51:08 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_exit_status(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc >> 8) & 255);
	return ((statloc & 127) + 128);
}

void	wait_process(int child_num)
{
	int	count;
	int	status;
	int	org_status;
	int	pid;

	count = 0;
	while (count < child_num)
	{
		pid = wait(&org_status);
		status = make_exit_status(org_status);
		if (pid == -1)
		{
			perror_exit("wait error");
		}
		else if (WIFSIGNALED(org_status))
		{
			g_exit_status = status;
		}
		else if (WIFEXITED(org_status))
		{
			g_exit_status = WEXITSTATUS(org_status);
		}
		count++;
	}
}
