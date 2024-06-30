/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:59:05 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 19:35:41 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_err_str(char *cmd, t_head *head)
{
	if (ft_strncmp(cmd, ">", 1) == 0)
	{
		if (cmd[1] == '\0')		// 있는거 그대로
			head->error_str = ft_strdup(">");
		else
			head->error_str = ft_strdup(">>");
	}
	if (ft_strncmp(cmd, "<", 1) == 0) // 
	{
		if (cmd[1] == '\0')		// 있는거 그대로
			head->error_str = ft_strdup("<");
		else
			head->error_str = ft_strdup("<<");
	}
	head->get_error = 10;
}

int	redir_err_flag(char *cmd, t_head *head)
{
	if (ft_strncmp(cmd, "<>", 2) == 0)
	{
		head->error_str = ft_strdup("<>");
		head->get_error = 10;
		return (0);
	}
	if (ft_strncmp(cmd, ">", 1) == 0)
	{
		if (cmd[1] ==  '\0' || ft_strncmp(cmd, ">>", 3) == 0)
			return (1);
		redir_err_str(&cmd[2], head);
	}
	if (ft_strncmp(cmd, "<", 1) == 0)
	{
		if (cmd[1] == '\0' || ft_strncmp(cmd, "<<", 3) == 0)
			return (1);
		redir_err_str(&cmd[2], head);
	}
	return (0);
}

void	redir_err_check(t_token *token, t_head *head)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if(tmp->redir_flag)
		{
			if (redir_err_flag(tmp->cmd, head))	// 정상적으로 나왔을때 다음꺼 확인
			{
				tmp = tmp->next;
				if (tmp == NULL || check_white_space(tmp->cmd))
				{
					head->get_error = 10;
					head->error_str = ft_strdup("newline");
					return ;
				}
				else
					continue;
			}
		}
		tmp = tmp->next;
	}
	return ;
}


// echo "$USER na"me
// echo '$USER na'me
// 						echo "$$USER"
// echo hi$USER
// echo hi"$USER"
// echo $USEEER
// echo ?$USER
