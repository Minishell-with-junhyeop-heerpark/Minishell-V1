/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/09 20:20:49 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_changed(char **str, int start, int end, t_token **filtered)
{
	char	*tmp;
	char	*changed;
	int		flag;

	flag = 0;
	changed = *str;
	while (start < end)
	{
		if (changed[start] == ' ')
		{
			ft_token_add(filtered, \
			token_new(ft_strndup(changed, start), 0));
			tmp = changed;
			changed = ft_strdup(&changed[start + 1]);
			free(tmp);
			start = 0;
			flag = 1;
		}
		start++;
	}
	*str = changed;
	return (flag);
}

char	*apply_env(char *cmd, t_list *env, int *ind, t_token **filtered)
{
	char	*changed;
	char	*key;
	char	*value;

	key = getkey(&cmd[*ind + 1]);
	value = env_find_value(key, env);
	if (!value)
		error_msg(0, NULL);
	changed = replace_cmd(cmd, key, value, ind);
	if (check_changed(&changed, *ind, *ind + ft_strlen(value), filtered))
		*ind = 0;
	else
		*ind = *ind + (ft_strlen(value) - 1 - ft_strlen(key));
	free(key);
	free(value);
	free(cmd);
	return (changed);
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
	(ft_strlen(str_exit) + ft_strlen(cmd) - 2) + 1);
	while (i < *ind)
		changed[i++] = cmd[j++];
	while (str_exit[k])
		changed[i++] = str_exit[k++];
	j += 2;
	while (cmd[j])
		changed[i++] = cmd[j++];
	changed[i] = 0;
	*ind = *ind + (ft_strlen(str_exit) - 2);
	free(cmd);
	free(str_exit);
	return (changed);
}

void	fill_elem(t_head *head, t_token *temp, t_process *process, char **cmd)
{
	t_token	*filtered;
	int		is_filename;
	int		flag;

	flag = 0;
	is_filename = 0;
	filtered = filtering(temp, process, cmd);
	while (filtered)
	{
		if (is_filename == 1)
		{
			set_fd(head, process, filtered->cmd, flag);
			is_filename = 0;
		}
		else if (filtered->redir_flag == 0)
		{
			my_strjoin(cmd, ft_strdup(filtered->cmd));
			my_strjoin(cmd, ft_strdup("\n"));
		}
		else if (filtered->redir_flag == 1)
		{
			flag = get_redir_flag(filtered->cmd, &is_filename);
		}
		filtered = filtered->next;
	}
}

int	no_cmd(t_head *head, t_process *process)
{
	if (process->exec_cmd[0] == NULL)
	{
		head->get_error = 1;
		if (check_redir_heredoc(process) == 1)
			process->is_error = 42;
		else if (check_redir_heredoc(process) == -1)
			process->is_error = 1;
		else
			process->is_error = 127;
		if (*(process->cmd) == '\n' && check_redir_heredoc(process) != -1)
		{
			print_bash_error(process->exec_cmd[0], "command not found", 127);
		}
		process->exec_path = NULL;
		return (1);
	}
	return (0);
}
