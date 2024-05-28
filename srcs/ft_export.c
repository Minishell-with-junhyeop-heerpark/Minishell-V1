/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 21:26:09 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_update(t_head *head, t_list **lst, char *key, char *value)
{
	t_list	*env;
	char	*str;

	env = *lst;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (!env->value)
			{
				env->value = value;
				return ;
			}
			else if (!value)
				return ;
			else
				str = export_strjoin(env->value, value);
			free(env->value);
			free(value);
			free(key);			
			env->value = str;
			return ;
		}
		env = env->next;
	}
	lstadd_back(&head->data->env->next, lst_new(key, value));
}

void	export_ext(t_head *head, t_list **lst, char *key, char *value)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			free(key);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	lstadd_back(&head->data->env->next, lst_new(key, value));
}

int	get_op(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			return (-1);
		if (cmd[i] == '=')
			break ;
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (1);		// += 
		i++;
	}
	return (0); 	// =
}

void	ft_export_ext(t_head *head, t_list *env)
{
	t_token	*tmp;
	char	*cmd;
	char	*key;
	char	*value;
	int		op;

	op = 0;
	tmp = head->top->token->next;
	while (tmp)
	{
		cmd = tmp->cmd;
		key = export_getkey(cmd, &op);
		if (key == NULL)
		{
			key_error(cmd);
			head->get_error = 1;
			tmp = tmp->next;
			continue ;
		}
		value = export_getvalue(cmd);
		if (op == 1)
			export_update(head, &env, key, value);
		else
			export_ext(head, &env, key, value);
		tmp = tmp->next;
	}
}

void	ft_export(t_head *head, char **exec_cmd)
{
	t_list	*tmp;

	(void)exec_cmd;
	if (head->top->token->next == NULL)
	{
		show_export(head);
		g_exit_status = 0;
		return ;
	}
	tmp = head->data->env->next;
	ft_export_ext(head, tmp);
	if (head->get_error)
		g_exit_status = 1;
}
