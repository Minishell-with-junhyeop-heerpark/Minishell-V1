/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:17:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/24 21:36:48 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***make_cmds(char **argv, int start_idx, int end_idx)
{
	char	***cmds;
	int		cmds_count;

	cmds = (char ***)malloc(sizeof(char **) * (end_idx - start_idx + 2));
	cmds_count = 0;
	while (start_idx <= end_idx)
	{
		cmds[cmds_count] = ft_split(argv[start_idx], ' ');
		if (cmds[cmds_count] == NULL)
			perror_exit("split error");
		cmds_count++;
		start_idx++;
	}
	cmds[cmds_count] = NULL;
	return (cmds);
}

void	free_cmds(int cmds_size, char ***cmds)
{
	int	i;

	i = 0;
	while (i < cmds_size)
	{
		free_splited(cmds[i]);
		i++;
	}
	free(cmds);
}
