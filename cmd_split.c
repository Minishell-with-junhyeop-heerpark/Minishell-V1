/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 08:08:06 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/17 08:38:59 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(char *redir[4])
{
	redir[0] = "<";
	redir[1] = "<<";
	redir[2] = ">";
	redir[3] = ">>";
}

int	cmd_split_cnt(char *str, char c)
{
	char	*redir[4];
	int		i;

	i = 0;
	init_redir(redir);
	while (str[i])
	{
		if (str[i] != ' ')
		{

		}
		i++;
	}
}

t_token	*cmd_split(char *str, char c)
{
	t_token	*res;
	int		n;
	int		i;

	res = (char **)malloc(sizeof(char *) * (cmd_split_cnt + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		
	}
	res[i] = 0;
	return (res);
}