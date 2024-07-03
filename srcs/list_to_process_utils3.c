/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/03 15:17:53 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*apply_exit_status(char *cmd, int *ind)
{
	char	*changed;
	char	*str_exit;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str_exit = ft_itoa(g_exit_status);
	changed = (char *)malloc(sizeof(char) * \
	(ft_strlen(str_exit) + ft_strlen(cmd) - 2) + 1);
	while (i < *ind)
		changed[i++] = cmd[j++];
	while (str_exit[k])
		changed[i++] = str_exit[k++];
	j += 2;
	while (cmd[j])
		changed[i++] = cmd[j++];
	changed[i] = 0;
	free(cmd);
	free(str_exit);
	*ind = *ind + 2;
	return (changed);
}

void	check_env(t_token *token, t_process *process)
{
	t_list	*env;
	char	*cmd;
	int		i;

	i = 0;
	cmd = token->cmd;
	env = process->env->next;
	while (cmd[i] != 0)
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
		{
			cmd = apply_exit_status(cmd, &i);
			token->cmd = cmd;
		}
		else if (cmd[i] == '$' && key_check(cmd[i + 1]) && cmd[i + 1] != '\"')
		{
			cmd = apply_env(token->cmd, env, &i);
			token->cmd = cmd;
		}
		else
			i++;
	}
}

void	concat_cmd(t_token *temp, t_process *process, char **cmd, char **str)
{
	if (temp->quote_flag == 0)
	{
		check_env(temp, process);
		*str = ft_strjoin(*cmd, temp->cmd);
		free(*cmd);
		*cmd = ft_strjoin(*str, "\n");
		free(*str);
	}
	else if (temp->quote_flag == 1)
	{
		*str = ft_strjoin(*cmd, temp->cmd);
		free(*cmd);
		*cmd = ft_strjoin(*str, "\n");
		free(*str);
	}
}

void	fill_elem(t_head *head, t_token *temp, t_process *process, char **cmd)
{
	char	*temp_str;
	int		is_filename;
	int		flag;

	flag = 0;
	is_filename = 0;
	while (temp)
	{
		if (is_filename == 1)
		{
			set_fd(head, process, temp->cmd, flag);
			is_filename = 0;
		}
		else if (temp->redir_flag == 0)
		{
			concat_cmd(temp, process, cmd, &temp_str);
		}
		else if (temp->redir_flag == 1)
		{
			is_filename = 1;
			flag = get_redir_flag(temp->cmd);
		}
		temp = temp->next;
	}
}

int	no_cmd(t_head *head, t_process *process)
{
	if (process->exec_cmd[0] == NULL)
	{
		printf("no_cmd!\n");
		head->get_error = 1;
		if (check_redir_heredoc(process) == 1)
			process->is_error = 42;
		else if (check_redir_heredoc(process) == -1)
			process->is_error = 1;
		else
			process->is_error = 127;
		if (*(process->cmd) == '\n')
			print_bash_error(process->exec_cmd[0], "command not found", 127);
		process->exec_path = NULL;
		return (1);
	}
	return (0);
}
