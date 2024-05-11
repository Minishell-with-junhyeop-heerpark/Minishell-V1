/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:25:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/11 17:31:56 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(char cmd)
{
	if (cmd == '<' || cmd == '>')
		return (1);
	return (0);
}

static int	check_redir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_redir(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	add_token_ext(t_token **lst, char *cmd, int *i, int *s)
{
	if (is_redir(cmd[*i]) && *i > *s)
	{
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 0, 0));
		*s = *i;
	}
	if (is_redir(cmd[*i]) && *i <= *s)
	{
		while (is_redir(cmd[*i]))
			*i += 1;
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 1, 0));
		*s = *i;
		return (0);
	}
	return (1);
}

void	add_token(t_token **lst, char *cmd)
{
	int		s;
	int		i;

	i = 0;
	s = 0;
	if (!check_redir(cmd))
	{
		ft_token_add(lst, token_new(ft_strdup(cmd), 0, 0));
		return ;
	}
	while (cmd[i])
	{
		if (add_token_ext(lst, cmd, &i, &s))
			i++;
	}
	if (i > s)
		ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0, 0));
}
