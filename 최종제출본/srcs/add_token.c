/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:25:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/07 17:55:53 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redir(char cmd)
{
	if (cmd == '<' || cmd == '>')
		return (1);
	return (0);
}

int	check_redir(char *cmd)
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

int	redir_size(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] != '>' && cmd[i] != '<')
			return (i);
		i++;
	}
	return (i);
}

void	my_quote_check(char c, int *q_flag, int *dq_flag)
{
	if (c == '\'' && !*dq_flag)
	{
		if (*q_flag)
			*q_flag = 0;
		else
			*q_flag = 1;
	}
	if (c == '\"' && !*q_flag)
	{
		if (*dq_flag)
			*dq_flag = 0;
		else
			*dq_flag = 1;
	}
}

void	add_token(t_token **lst, char *cmd)
{
	t_token_var	t;

	t = (t_token_var){0, 0, 0, 0};
	if (!cmd)
		return ;
	while (cmd[t.i])
	{
		my_quote_check(cmd[t.i], &t.q_flag, &t.dq_flag);
		if (is_redir(cmd[t.i]) && !t.q_flag && !t.dq_flag)
		{
			if (t.i - t.s > 0)
				ft_token_add(lst, token_new(ft_strndup(&cmd[t.s], \
				t.i - t.s), 0));
			ft_token_add(lst, token_new(ft_strndup(&cmd[t.i], \
			redir_size(&cmd[t.i])), 1));
			t.i += redir_size(&cmd[t.i]);
			t.s = t.i;
		}
		else
			t.i++;
	}
	if (t.i - t.s > 0)
		ft_token_add(lst, token_new(ft_strndup(&cmd[t.s], t.i - t.s), 0));
	free(cmd);
}
