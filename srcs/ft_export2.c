/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:23:55 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/30 14:59:57 by junhyeop         ###   ########.fr       */
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

void	key_error(char *key)
{
	g_exit_status = 1;
	printf("minishell: export: `%s': not a valid identifier\n", key);
}

int	key_validate(char *key)
{
	int	i;

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
		error_msg(0);
	while (v.s < v.n)
	{
		value[v.s] = cmd[v.i - v.n + v.s];
		v.s++;
	}
	value[v.s] = 0;
	return (value);
}
