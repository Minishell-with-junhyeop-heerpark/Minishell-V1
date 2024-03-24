/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:03 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/24 22:38:29 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	**make_pipe(int child_num)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = (int **)malloc(sizeof(int *) * (child_num));
	if (!pipes)
		exit(1);
	while (i < child_num)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
			perror_exit("pipe malloc");
		if (pipe(pipes[i]) == -1)
			perror_exit("pipe");
		i++;
	}
	return (pipes);
}

void	free_pipe(int **pipe, int child_num)
{
	int	i;

	i = 0;
	while (i < child_num)
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
}
