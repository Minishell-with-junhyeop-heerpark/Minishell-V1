/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:26:53 by junhyeong         #+#    #+#             */
/*   Updated: 2024/07/07 17:41:48 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*dquote_parsing(char *str, t_process *process, int *ind)
{
	t_list	*env;
	int		i;

	*ind = *ind + 1;
	i = *ind;
	env = process->env->next;
	while (str[i])
	{
		if (str[i] == '\"')
			break ;
		if (str[i] == '$' && str[i + 1] == '?')
			str = add_exit_status(str, &i);
		else if (str[i] == '$' && key_check(str[i + 1]) && str[i + 1] != '\"')
			str = add_env(str, env, &i, *ind);
		else
			i++;
		if (i <= 0)
			i = *ind;
	}
	str = replace_str(str, i, *ind);
	*ind = i - 1;
	return (str);
}

char	*replace_str(char *str, int end, int start)
{
	int		i;
	int		len;
	char	*changed;

	i = 0;
	len = ft_strlen(str) - 2;
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
	int	i;

	*ind = *ind + 1;
	i = *ind;
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		i++;
	}
	str = replace_str(str, i, *ind);
	*ind = i - 1;
	return (str);
}

char	*token_to_cmd(char *str, t_process *process)
{
	int		i;
	int		max;
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
		if (i < 0)
			i = 0;
		max = ft_strlen(str);
		if (i >= max)
			break ;
	}
	return (str);
}

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
		token = token->next;
		free(tmp);
	}
	process->filtered = filtered;
	return (filtered);
}
