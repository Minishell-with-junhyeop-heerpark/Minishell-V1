/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:25:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/01 13:07:55 by heerpark         ###   ########.fr       */
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

int	add_token_ext(t_token **lst, char *cmd, int *i, int *s)
{
	if (is_redir(cmd[*i]) && *i > *s)
	{
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 0));
		*s = *i;
	}
	if (is_redir(cmd[*i]) && *i <= *s)
	{
		while (is_redir(cmd[*i]))
			*i += 1;
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 1));
		*s = *i;
		return (0);
	}
	return (1);
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

// cmd 분리하면서 `>` 신경쓰기? -> quote 내부이면 신경 안씀!
void 	add_token(t_token **lst, char *cmd)
{
	int	i;
	int q_flag;
	int dq_flag;
	int	s;

	i = 0;
	s = 0;
	q_flag = 0;
	dq_flag = 0;
	// printf("add_token : %s\n", cmd);
	if (!cmd)
		return ;
	while (cmd[i])
	{
		my_quote_check(cmd[i], &q_flag, &dq_flag); // quote 체크
		if (is_redir(cmd[i]) && !q_flag && !dq_flag)
		{
			printf("reidr len: %zu\n", ft_strlen(&cmd[i]));
			if (i - s > 0)
				ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0));
			ft_token_add(lst, token_new(ft_strndup(&cmd[i], redir_size(&cmd[i])), 1));
			i += redir_size(&cmd[i]);
			printf("reidr size: %d\n", i);
			s = i;
		}
		else
			i++;
	}
	if (i - s > 0)
		ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0));
	free(cmd);
}

// void	add_token(t_token **lst, char *cmd)
// {
// 	int		s;
// 	int		i;

// 	i = 0;
// 	s = 0;
// 	// if (!check_redir(cmd)) // 나중에 quote 제거할 때 해주기 
// 	// {
// 	// 	ft_token_add(lst, token_new(ft_strdup(cmd), 0, 0));
// 	// 	free(cmd);
// 	// 	return ;
// 	// }
// 	while (cmd[i])
// 	{
// 		if (add_token_ext(lst, cmd, &i, &s))
// 			i++;
// 	}
// 	if (i > s)
// 		ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0, 0));
// 	free(cmd);
// }

int	add_token_ext2(t_token **lst, char *cmd, int *i, int *s)
{
	if (is_redir(cmd[*i]) && *i > *s)
	{
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 0));
		*s = *i;
	}
	if (is_redir(cmd[*i]) && *i <= *s)
	{
		while (is_redir(cmd[*i]))
			*i += 1;
		ft_token_add(lst, token_new(ft_strndup(&cmd[*s], *i - *s), 1));
		*s = *i;
		return (0);
	}
	return (1);
}

void	add_token2(t_token **lst, char *cmd, int qf)
{
	int		s;
	int		i;

	i = 0;
	s = 0;
	(void)qf; // 
	if (!check_redir(cmd))
	{
		ft_token_add(lst, token_new(ft_strdup(cmd), 0));
		free(cmd);
		return ;
	}
	while (cmd[i])
	{
		if (add_token_ext2(lst, cmd, &i, &s))
			i++;
	}
	if (i > s)
		ft_token_add(lst, token_new(ft_strndup(&cmd[s], i - s), 0));
	free(cmd);
}
