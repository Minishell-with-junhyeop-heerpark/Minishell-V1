/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:47 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/28 16:41:46 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_flag(char	*token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strncmp(token, ">", 2) == 0)
			return (1);
		else if (ft_strncmp(token, "<", 2) == 0)
			return (3);
	}
	else if (ft_strlen(token) == 2)
	{
		if (ft_strncmp(token, ">>", 3) == 0)
			return (2);
		else if (ft_strncmp(token, "<<", 3) == 0)
			return (4);
	}
	return (0);
}

void	close_unused_input(t_process *process)
{
	if (process->heredoc_fd != -42)
	{
		if (process->heredoc_fd != -1)
		{
			close(process->heredoc_fd);
			unlink(process->heredoc_filename);
		}
		process->heredoc_fd = -42;
	}
	if (process->re_infile_fd != -42)
	{
		if (process->re_infile_fd != -1)
		{
			close(process->re_infile_fd);
		}
		process->re_infile_fd = -42;
	}
}

void	close_unused_output(t_process *process)
{
	if (process->re_append_fd != -42)
	{
		if (process->re_append_fd != -1)
			close(process->re_append_fd);
		process->re_append_fd = -42;
	}
	if (process->re_outfile_fd != -42)
	{
		if (process->re_outfile_fd != -1)
			close(process->re_outfile_fd);
		process->re_outfile_fd = -42;
	}
}

void	set_fd(t_head *head, t_process *process, char *file_name, int redir_flag)
{
	if (redir_flag == 1)
	{
		close_unused_output(process);
		process->re_outfile_fd = get_outfile(head, file_name);
	}
	else if (redir_flag == 2)
	{
		close_unused_output(process);
		process->re_append_fd = get_append(head, file_name);
	}
	else if (redir_flag == 3)
	{
		close_unused_input(process);
		process->re_infile_fd = get_infile(head, file_name);
	}
	else if (redir_flag == 4)
	{
		close_unused_input(process);
		process->heredoc_fd = get_heredoc(head, process, file_name);
	}
}

char	*getkey(char *str)
{
	char	*dest;
	int		n;
	int 	i;

	n = 0;
	i = 0;
	while (str[n] && str[n] != ' ' && str[n] != '$')
		n++;
	dest = (char *)malloc(sizeof(char) * n + 1);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*env_find_value(char *key, t_list *envp)
{
	// int	i;

	// i = 0;
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (ft_strdup(""));
}

void	replace_value(char *new_cmd, int *ind, char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		new_cmd[*ind] = value[i];
		*ind += 1;
		i++;
	}
}

char	*replace_cmd(char *cmd, char *key, char *value, int *ind)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - (ft_strlen(key) + 1) + ft_strlen(value) + 1));

	while (i < *ind)
		new_cmd[j++] = cmd[i++];

	replace_value(new_cmd, &j, value);
	i += ft_strlen(key) + 1;

	while (cmd[i])
		new_cmd[j++] = cmd[i++];

	new_cmd[j] = 0;
	return (new_cmd);
}

char	*apply_env(char *cmd, t_list *env, int *ind)
{
	char	*changed;
	char	*key;
	char	*value;

	// printf("cmd : %s\n", cmd);
	key = getkey(&cmd[*ind + 1]);	// 하나 지나서 보내기 $HOME 이면 H부터!
	value = env_find_value(key, env);
	// printf("key : %s\nvalue: %s\n", key, value);
	if (!value)
		error_msg(0);
	changed = replace_cmd(cmd, key, value, ind);
	*ind = *ind + ft_strlen(value);
	// printf("ind : %d\n", *ind);
	free(key);
	free(value);
	free(cmd);
	return (changed);
}

//"   $HOME" -> $HOME
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
	changed = (char *)malloc(sizeof(char) * (ft_strlen(str_exit) + ft_strlen(cmd) - 2 ) + 1); // -2는 $? 를 치환하기 때문이다
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
	return(changed);
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
		else if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != '\"')
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
	if (process->exec_cmd[0] == NULL) // ""이런 케이스는 여기에 걸림.
	{
		head->get_error = 1;
		if (*(process->cmd) == '\n')
			print_bash_error(process->exec_cmd[0], "command not found", 127);
		process->exec_path = NULL;
		return (1);
	}
	return (0);
}

void	set_builtin(t_head *head, t_process *process, char **exec_cmd)
{
	if (exec_cmd[1] && ft_strncmp(exec_cmd[1], "~", 1) == 0)
	{
		if (ft_strncmp(exec_cmd[1], "~/", 2) == 0)
			add_homepath(head, &exec_cmd[1], 0);
		else
			add_homepath(head, &exec_cmd[1], 1);
	}
	process->exec_path = NULL;
	return ;
}

void	set_exec(t_head *head, t_process *process, char **path, int i)
{
	char	*exec_path;
	char	*test_path;

	while (path[i])
	{
		test_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(test_path, process->exec_cmd[0]);
		if (access(exec_path, X_OK) == 0)
		{
			i = -1;
			free(test_path);
			break ;
		}
		free(test_path);
		free(exec_path);
		i++;
	}
	if (i != -1)
	{
		exec_path = NULL;
		print_bash_error(process->exec_cmd[0], "command not found", 127);
		head->get_error = 1;
		if (process->heredoc_fd != -42)
			unlink(process->heredoc_filename);
	}
	process->exec_path = exec_path;
}

void	set_process(t_head *head, t_process *process, char **path)
{
	char	**exec_cmd;

	exec_cmd = ft_split(process->cmd, '\n');
	process->exec_cmd = exec_cmd;
	if (no_cmd(head, process)) // 여기서 종료될 때 exec_cmd free 생각하자.
		return ;
	if (is_builtin(exec_cmd))
		set_builtin(head, process, exec_cmd);
	else if (is_filepath(exec_cmd))
	{
		if (ft_strncmp(exec_cmd[0], "~", 1) == 0)
			add_homepath(head, &exec_cmd[0], 0);
		process->exec_path = NULL;
	}
	else
	{
		set_exec(head, process, path, 0);
	}
}

void	init_process(t_process *process)
{
	process->heredoc_filename = NULL;
	process->cmd = NULL;
	process->exec_cmd = NULL;
	process->exec_cmd = NULL;
}

t_process	*get_process(t_head *head, t_list *line, char **path)
{
	t_process	*process;
	t_token		*temp;
	char		*cmd;

	process = (t_process *)malloc(sizeof(t_process));
	init_process(process);
	process->env = head->data->env;
	cmd = ft_strdup("");
	temp = line->token;
	init_fd(process);
	fill_elem(head, temp, process, &cmd);
	process->cmd = cmd;
	set_process(head, process, path);
	return (process);
}

