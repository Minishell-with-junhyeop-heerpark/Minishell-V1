/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:05:39 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/23 16:00:26 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// 1. key 값 유효성 체크하기 
// 2. 왜 env하면 LS_COLORS가 여러개 나오는지?
char	*export_getkey(char **exec_cmd, t_head *head)
{
	int		n;
	int		i;
	char	*str;
	char	*key;

	(void)exec_cmd;
	n = 0;
	i = 0;
	str = head->top->token->next->cmd;
	while (str[n] && str[n] != '=')
	{
		if (str[n] == ' ')
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

typedef struct s_value_var
{
	int n;
	int i;
	int s;
}	t_value_var;

char	*export_getvalue(t_head *head)
{
	t_value_var	v;
	char		*value;
	char		*cmd;

	v = (struct s_value_var){0, 0, 0};
	cmd = head->top->token->next->cmd;
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
	printf("===================safe=====================\n");
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

void	ft_export(t_head *head, char **exec_cmd)
{
	t_list	*tmp;
	char	*key;
	char	*value;
	int		i;

	if (head->top->token->next == NULL)
	{
		show_export(head);
		return ;
	}
	tmp = head->data->env->next;
	while (tmp->next)
		tmp = tmp->next;
	i = 0;
	key = export_getkey(exec_cmd, head);
	value = export_getvalue(head);
	printf("key: %s, value : %s\n", key, value);
	lstadd_back(&tmp, lst_new(key, value));
	
}
