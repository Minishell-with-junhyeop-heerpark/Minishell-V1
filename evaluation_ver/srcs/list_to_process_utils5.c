/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:27:32 by junhyeong         #+#    #+#             */
/*   Updated: 2024/07/09 18:20:45 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	key_isalnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	filter_lst_add(t_head *head, t_list *new)
{
	t_list	*tmp;

	tmp = head->filtered;
	if (tmp == NULL)
	{
		head->filtered = new;
		return ;
	}
	else if (tmp == NULL && new == NULL)
		return ;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_list	*list_new(t_token *token)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(0, NULL);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->token = token;
	return (newnode);
}

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
	*ind = *ind + ft_strlen(str_exit) - 2;
	free(cmd);
	free(str_exit);
	return (changed);
}

char	*getkey(char *str)
{
	char	*dest;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (ft_isdigit(str[0]) && ft_isdigit(str[1]))
		return (ft_strndup(str, 1));
	while (str[n] && str[n] != '$' && str[n] != '\'' && str[n] != '\"' \
	&& str[n] != ' ' && key_isalnum(str[n]))
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
