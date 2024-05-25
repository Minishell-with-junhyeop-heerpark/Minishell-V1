/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/25 16:47:17 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_op(char *cmd);

void	free_show_list(t_list **top)
{
	t_list	*tmp;
	t_list	*rmv;

	tmp = *top;
	while (tmp)
	{
		rmv = tmp;
		free(rmv->key);
		if (rmv->value)
			free(rmv->value);
		tmp = rmv->next;
		free(rmv);
	}
}

void	key_error(char *key)
{
	g_exit_status = 1;
	printf("minishell: export: `%s': not a valid identifier\n", key);
}

int	key_validate(char *key)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
	{
		free(key);
		return (0);
	}
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			free(key);
			return (0);
		}
		i++;
	}
	return (1);
}

// 1. key 값 유효성 체크하기 
// 2. 왜 env하면 LS_COLORS가 여러개 나오는지?
char	*export_getkey(char *cmd, int *op)
{
	int		n;
	int		i;
	char	*key;

	n = 0;
	i = 0;
	*op = get_op(cmd);
	if (*op == -1)
		return (NULL);
	while (cmd[n] && cmd[n] != '=')
	{
		if (cmd[n] == ' ')
			return (NULL);
		n++;
	}
	key = (char *)malloc(sizeof(char) * n + 1 - *op);
	while (i + *op < n)
	{
		key[i] = cmd[i];
		i++;
	}
	key[i] = 0;
	if (!key_validate(key))
		return (NULL);
	return (key);
}

typedef struct s_value_var
{
	int n;
	int i;
	int s;
}	t_value_var;

char	*export_getvalue(char *cmd)
{
	t_value_var	v;
	char		*value;

	v = (struct s_value_var){0, 0, 0};
	while (cmd[v.i] && cmd[v.i] != '=')
		v.i++;
	if (cmd[v.i] == '\0')
		return (NULL);
	while (cmd[v.i++])
		v.n++;
	value = (char *)malloc(sizeof(char) * v.n + 1);
	if (!value)
		error_msg(1);
	while (v.s < v.n)
	{
		value[v.s] = cmd[v.i - v.n + v.s];
		v.s++;
	}
	value[v.s] = 0;
	return (value);
}

void	export_add_prev(t_list **lst, t_list *new, t_list **top)
{
	t_list	*tmp;

	(void)top;
	tmp = *lst;
	if (!new)
		error_msg(1);
	// if (ft_strcmp(tmp->key, (*top)->key) == 0)
	// {
	// 	printf("push first node\n");
	// 	new->next = tmp;
	// 	tmp->prev = new;
	// 	*top = new;
	// 	return ;
	// }
	// printf("push here\n");
	new->next = tmp;
	new->prev = tmp->prev;
	tmp->prev->next = new;
	tmp->prev = new;
	// printf("push here\n");

}
void	sorting(t_list *t_env, t_list **top)
{
	t_list	*tmp;
	t_list	*new;
	
	tmp = *top;
	if (tmp->next == NULL || ft_strcmp(tmp->key, t_env->key) > 0) //tmp->key 가 더 위에 있어야하는 경우
	{
		// printf("\nadd_first_prev\n");
		// export_add_prev(&tmp, lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)), top);
		new = lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value));
		tmp->prev = new;
		new->next = tmp;
		*top = new;
		return ;
	}
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, t_env->key) > 0)
		{
			// printf("\nadd_prev\n");
			export_add_prev(&tmp, lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)), top);
			return ;
		}
		tmp = tmp->next;
	}
	// if (ft_strcmp(tmp->next->key, t_env->key) > 0)
	// 	export_add_prev(&tmp->next, lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)), top);
	// else
	// 여기가 문제!!!!!!!!!!!!
	lstadd_back(top, lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)));
}

// void	print_top(t_list **top)
// {
// 	t_list *tmp;

// 	tmp = *top;
// 	printf("-----------------test ----------\n");
// 	while (tmp)
// 	{
// 		printf("> %s=%s\n", tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// }


void	sort_list(t_list *env, t_list **top)
{
	t_list	*t_env;
	// t_list	*new;
	// t_list	*top;

	t_env = env;
	*top = lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)); 
	t_env = t_env->next;
	while (t_env)
	{
		printf("%s, %s\n", t_env->key, t_env->value);
		sorting(t_env, top);
		// print_top(top);
		t_env = t_env->next;
	}
}


void	show_export(t_head *head)
{
	t_list	*env;
	t_list	*top;
	t_list	*tmp;

	top = NULL;
	env = head->data->env->next;
	sort_list(env, &top);
	if (!top)
		error_msg(1);
	tmp = top;
	while (tmp)
	{
		printf("declare -x ");
		if (tmp->value)
			printf("%s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n",tmp->key);
		tmp = tmp->next;
	}
	free_show_list(&top);
}

char	*export_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return ((char *)str);
}

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
