/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 20:06:50 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	(ft_strlen(str_exit) + ft_strlen(cmd) - 2 ) + 1);
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


char	*add_exit_status(char *cmd, int *ind)
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
	(ft_strlen(str_exit) + ft_strlen(cmd) - 2 ) + 1);
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
	// *ind = *ind + 2;
	return (changed);
}


char	*dquote_parsing(char *str, t_process *process, int *ind)
{
	int 		i;
	t_list	*env;

	*ind = *ind + 1;
	i = *ind;
	env = process->env->next;
	while (str[i])
	{
		if (str[i] == '\"')
			break ;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str = add_exit_status(str, &i);
		}
		else if (str[i] == '$' && key_check(str[i + 1]) && str[i + 1] != '\"')
		{
			str = apply_env(str, env, &i);
		}
		else
			i++;
	}
	str = replace_str(str, i, *ind);
	*ind = 0;
	return (str);
}


char	*replace_str(char *str, int end, int start)
{
	int		i;
	int		len;
	char	*changed;

	i = 0;
	len = ft_strlen(str) - 2; // 1 - 1
	changed = (char *)malloc(sizeof(char) * len + 1);
	while (i < start - 1)
	{
		changed[i] = str[i];
		i++;
	}
	while (start < end)
		changed[i++] = str[start++];
	while (str[++end])
		changed[i++] = str[end]; 
	changed[i] = 0;
	free(str);
	return (changed);
}


char	*quote_parsing(char *str, int *ind)
{
	int i;

	*ind = *ind + 1;
	i = *ind;
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		i++;
	}
	str = replace_str(str, i, *ind);
	// ft_token_add(&filtered, token_new(ft_strndup(str, i - 2), 0));
	// my_strjoin(&tmp, ft_strndup(&str[1], i - 1));
	*ind = 0;
	return (str);
}


char	*token_to_cmd(char *str, t_process *process)
{
	int			i;
	t_list	*env;

	env = process->env->next;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str = quote_parsing(str, &i);
		else if (str[i] == '\"')
			str = dquote_parsing(str, process, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
			str = apply_exit_status(str, &i);
		else if (str[i] == '$' && key_check(str[i + 1]) && str[i + 1] != '\"')
			str = apply_env(str, env, &i);
		else
			i++;
	}
	return str;
}

// 토큰이랑 cmd함께 만들기?
t_token	*filtering(t_token *token, t_process *process, char **cmd, t_head *head)
{
	t_token	*filtered;
	char		*str;
	char		*tmp;

	(void)cmd;
	filtered = NULL;
	while (token)
	{
		str = ft_strdup(token->cmd);
		tmp = token_to_cmd(str, process);
		if (!tmp)
			error_msg(1, NULL);
		if (token->redir_flag)
			ft_token_add(&filtered, token_new(ft_strdup(tmp), 1));
		else
			ft_token_add(&filtered, token_new(ft_strdup(tmp), 0));
		// my_strjoin(cmd, ft_strdup(tmp));
		// my_strjoin(cmd, ft_strdup("\n"));
		token = token->next;
		free(tmp);
	}
	head->filtered->token = filtered;
	return (filtered);
}
// echo 'a''b''c''d'''sdf''''''''df''''
// 여기부터 
// temp가 내가 파싱한 명령어 -> cmd에다가 담기!
void	fill_elem(t_head *head, t_token *temp, t_process *process, char **cmd)
{
	t_token	*filtered;
	int		is_filename;
	int		flag;

	flag = 0;
	is_filename = 0;
	filtered = filtering(temp, process, cmd, head);
	// t_token *a = head->filtered->token;
	// while (a)
	// {
	// 	printf(".... %s %d %d\n", a->cmd, a->redir_flag, a->quote_flag);
	// 	a = a->next;
	// }
	printf(".... |\n");
	// printf("filter next : %s\n")
	while (filtered)
	{
		if (is_filename == 1)
		{
			// printf("file start %s\n", filtered->cmd);
			set_fd(head, process, filtered->cmd, flag);
			is_filename = 0;
		}
		else if (filtered->redir_flag == 0)
		{
			// concat_cmd(temp, process, cmd, &temp_str);
			my_strjoin(cmd, ft_strdup(filtered->cmd));
			my_strjoin(cmd, ft_strdup("\n"));
		}
		else if (filtered->redir_flag == 1)
		{
			is_filename = 1;
			flag = get_redir_flag(filtered->cmd);
		}
		filtered = filtered->next;
	}
}

int	no_cmd(t_head *head, t_process *process)
{
	if (process->exec_cmd[0] == NULL)
	{
		head->get_error = 1;
		if (*(process->cmd) == '\n')
			print_bash_error(process->exec_cmd[0], "command not found", 127);
		process->exec_path = NULL;
		return (1);
	}
	return (0);
}
