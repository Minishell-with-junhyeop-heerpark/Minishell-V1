/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/03 19:58:03 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	filter_lst_add(t_head *head, t_list *new)
{
	t_list	*tmp;

	tmp = head->filtered;
	if (tmp == NULL)
	{
		head->filtered = new;
		return ;
	}
	else if (tmp == NULL && new == NULL)
		return ;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_list	*list_new(t_token *token)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(0, NULL);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->token = token;
	return (newnode);
}

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
	*ind = *ind + ft_strlen(str_exit) - 2;
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

char	*apply_env(char *cmd, t_list *env, int *ind)
{
	char	*changed;
	char	*key;
	char	*value;

	key = getkey(&cmd[*ind + 1]);
	value = env_find_value(key, env);
	if (!value)
		error_msg(0, NULL);
	changed = replace_cmd(cmd, key, value, ind);
	*ind = *ind + (ft_strlen(value) - 1 - ft_strlen(key));
	free(key);
	free(value);
	free(cmd);
	return (changed);
}

char	*add_exit_status(char *cmd, int *ind, int *cnt)
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
	*cnt = *cnt + (ft_strlen(str_exit) - 2);
	*ind = 0;
	return (changed);
}


char	*dquote_parsing(char *str, t_process *process, int *ind)
{
	int 		i;
	int			cnt;
	t_list		*env;

	cnt = 0;
	*ind = *ind + 1;
	i = *ind;
	env = process->env->next;
	while (str[i])
	{
		if (str[i] == '\"')
			break ;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			str = add_exit_status(str, &i, &cnt);
		}
		else if (str[i] == '$' && key_check(str[i + 1]) && str[i + 1] != '\"')
		{
			str = add_env(str, env, &i, &cnt);
		}
		else
			i++;
	}
	str = replace_str(str, i, *ind);
	*ind = *ind + cnt;
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
	// *ind -= 2;
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
		printf("str:%s %d\n",str, i);
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
		if (i < 0)
			i = 0;
	}
	return str;
}

// 토큰이랑 cmd함께 만들기?
t_token	*filtering(t_token *token, t_process *process, char **cmd)
{
	t_token		*filtered;
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
	// printf("ih\n");
	// filter_lst_add(head, list_new(filtered));
	process->filtered = filtered;
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
	filtered = filtering(temp, process, cmd);
	t_token *a = filtered;
	while (a)
	{
		printf(".... %s %d %d\n", a->cmd, a->redir_flag, a->quote_flag);
		a = a->next;
	}
	printf(".... |\n");
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
			printf("filler->cmd: %s\n", filtered->cmd);
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
