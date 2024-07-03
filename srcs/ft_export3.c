/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:25:38 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 19:16:09 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_add_prev(t_list **lst, t_list *new, t_list **top)
{
	t_list	*tmp;

	(void)top;
	tmp = *lst;
	if (!new)
		error_msg(0, NULL);
	new->next = tmp;
	new->prev = tmp->prev;
	tmp->prev->next = new;
	tmp->prev = new;
}

void	sorting(t_list *t_env, t_list **top)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *top;
	if (tmp->next == NULL || ft_strcmp(tmp->key, t_env->key) > 0)
	{
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
			export_add_prev(&tmp, lst_new(ft_strdup(t_env->key), \
			ft_strdup(t_env->value)), top);
			return ;
		}
		tmp = tmp->next;
	}
	lstadd_back(top, lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value)));
}

void	sort_list(t_list *env, t_list **top)
{
	t_list	*t_env;

	t_env = env;
	*top = lst_new(ft_strdup(t_env->key), ft_strdup(t_env->value));
	t_env = t_env->next;
	while (t_env)
	{
		// printf("%s, %s\n", t_env->key, t_env->value);
		sorting(t_env, top);
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
		error_msg(0, NULL);
	tmp = top;
	while (tmp)
	{
		printf("declare -x ");
		if (tmp->value)
			printf("%s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
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
