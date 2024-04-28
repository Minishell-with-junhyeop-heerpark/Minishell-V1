/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:15:47 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/28 23:00:48 by junhyeop         ###   ########.fr       */
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

void	set_fd(t_process *process, char *file_name, int redir_flag)
{
	if (redir_flag == 1)
	{
		process->re_outfile_fd = get_outfile(file_name);
		process->re_append_fd = -42;
	}
	else if (redir_flag == 2)
	{
		process->re_append_fd = get_append(file_name);
		process->re_outfile_fd = -42;
	}
	else if (redir_flag == 3)
	{
		process->re_infile_fd = get_infile(file_name);
		process->heredoc_fd = -42;
	}
	else if (redir_flag == 4)
	{
		process->heredoc_fd = get_heredoc(process, file_name);
		process->re_infile_fd = -42;
	}
	else
		perror_exit("set_fd");
}

///////////////////////////////////////////////////////////
/* junhyeop */

char	*getkey(char *str)
{
	char	*dest;
	int		n;
	int 	i;

	n = 0;
	i = 0;
	while (str[n] != ' ')
		n++;
	dest = (char *)malloc(sizeof(char) * i + 1);
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
	int	i;

	i = 0;
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
		{
			printf("envp value : %s\n", envp->value);
			return (envp->value);
		}
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

char	*replace_cmd(char *cmd, char *key, char *value)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = (char *)malloc(sizeof(char) * \
		(ft_strlen(cmd) - (ft_strlen(key) + 1) + ft_strlen(value) + 1));
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			replace_value(new_cmd, &j, value);
			i += ft_strlen(key) + 1;
		}
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = 0;
	return (new_cmd);
}

char	*apply_env(char *cmd, t_list *env, int ind)
{
	char	*changed;
	char	*key;
	char	*value;

	key = getkey(&cmd[ind + 1]);	// $ 넘겨서 보내기
	value = env_find_value(key, env);
	if (!value)
		error_msg(1);
	changed = replace_cmd(cmd, key, value);
	free(key);
	free(value);
	free(cmd);
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
		if (cmd[i] == '$')
			cmd = apply_env(cmd, env, i);
		i++;
	}
	token->cmd = cmd;
	printf("cmd -> %s\n", cmd);
}

void	fill_elem(t_token *temp, t_process *process, char **cmd, int flag)
{
	(void)cmd;

	char	*temp_str;
	int		is_filename;

	is_filename = 0;
	while (temp)
	{
		printf("flag -  > %d\n",temp->quote_flag);
		if (is_filename == 1)
		{
			set_fd(process, temp->cmd, flag);
			is_filename = 0;
		}
		else if (temp->redir_flag == 0 && temp->quote_flag == 0)
		{
			check_env(temp, process);
			// if (ft_strncmp(temp->cmd, "$", 1) == 0)
			// {
			// 	get_node_value(process->env, temp);
			// }
			printf("check env\n\n");
			temp_str = ft_strjoin(*cmd, temp->cmd);
			free(*cmd);
			*cmd = ft_strjoin(temp_str, " ");
			free(temp_str);
		}
		else if (temp->redir_flag == 0 && temp->quote_flag == 1)
		{
			temp_str = ft_strjoin(*cmd, temp->cmd);
			free(*cmd);
			*cmd = ft_strjoin(temp_str, " ");
			free(temp_str);
		}
		else if (temp->redir_flag == 1)
		{
			is_filename = 1;
			flag = get_redir_flag(temp->cmd);
		}
		temp = temp->next;
	}
}

//////////////////////////////////////////////////////////////////////


void	set_process(t_head *head, t_process *process, char **path)
{
	char	**exec_cmd;
	char	*exec_path;
	char	*test_path;
	int		i;

	i = 0;
	exec_cmd = ft_split(process->cmd, ' ');
	if (exec_cmd[0] == NULL)
	{
		unlink(process->heredoc_filename);
		perror_exit("no cmd");
	}
	process->exec_cmd = exec_cmd;
	// printf("%s\n%s\n", process->exec_cmd[0], process->exec_cmd[1]);
	if (is_builtin(exec_cmd))
	{
		if (exec_cmd[1] && ft_strncmp(exec_cmd[1], "~", 1) == 0)
		{
			if (ft_strncmp(exec_cmd[1], "~/", 2) == 0)
				add_homepath(head, &exec_cmd[1], 0);
			else
				add_homepath(head, &exec_cmd[1], 1);
		}
		return ;
	}
	if (is_filepath(exec_cmd))
	{
		printf("im in file_path\n");
		if (ft_strncmp(exec_cmd[0], "~", 1) == 0)
			add_homepath(head, &exec_cmd[0], 0);
		return ;
	}
	while (path[i])
	{
		test_path = ft_strjoin(path[i], "/");
		exec_path = ft_strjoin(test_path, exec_cmd[0]);
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
		perror_exit("set_process");
	// process->exec_cmd = exec_cmd;
	process->exec_path = exec_path;
}

t_process	*get_process(t_head *head, t_list *line, char **path)
{
	t_process	*process;
	t_token		*temp;
	char		*cmd;

	process = (t_process *)malloc(sizeof(t_process));
	process->env = head->data->env;
	cmd = ft_strdup("");
	temp = line->token;
	init_fd(process);
	fill_elem(temp, process, &cmd, 0);
	process->cmd = cmd;
	set_process(head, process, path);
	printf("set_process end\n");
	return (process);
}
