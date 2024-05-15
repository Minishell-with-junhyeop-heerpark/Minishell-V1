/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/15 22:38:47 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_getkey(char **exec_cmd)
{
	int		n;
	int		i;
	char	*str;
	char	*key;
	
	n = 0;
	i = 0;
	str = exec_cmd[1];
	while (str[n] != '=')
	{
		if (str[n] || str[n] == ' ')
			return (NULL);
		n++;
	}
	key = (char *)malloc(sizeof(char) * n + 1);
	while (i < n)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = 0;
	return (key);
}

char	*export_getvalue(char **exec_cmd, t_head *head)
{
	int		n;
	int		i;
	int		s;
	char	*value;
	char	*cmd;

	(void)exec_cmd;
	i = 0;
	n = 0;
	s = 0;
	cmd = head->top->token->next->cmd;
	while (cmd[i] && cmd[i] != '=')
		i++;
	while (cmd[i++])
		n++;
	value = (char *)malloc(sizeof(char) * n + 1);
	if (!value)
		error_msg(1);
	while (s < n)
		value[s++] = cmd[i - n - 1];
	value[s] = 0;
	return (value);
}


// t_env	*sort(t_list *env)
// {
// 	return NULL;	
// }

void	show_export(t_head *head)
{
	t_list	*env;

	env = head->data->env->next;
	while (env)
	{
		printf("declare -x ");
		// sort(env);
		printf("%s=\"%s\"", env->key, env->value);
	}
}

void	ft_export(t_head *head, char **exec_cmd)
{
	t_list	*tmp;
	char	*key;
	char	*value;
	int		n;
	int		i;

	tmp = head->data->env->next;
	while (tmp->next)
		tmp = tmp->next;
	i = 0;
	n = sizeof(exec_cmd)/4;
	if (n == 1)
	{
		show_export(head);
		return ;
	}
	key = export_getkey(exec_cmd);
	value = export_getvalue(exec_cmd, head);
	lstadd_back(&tmp, lst_new(key, value));
}
