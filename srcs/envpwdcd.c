/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpwdcd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:27:15 by heerpark          #+#    #+#             */
/*   Updated: 2024/06/01 15:59:53 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		print_bash_error("", "can't implement pwd", 1);
		g_exit_status = 1;
	}
}

void	env(t_head *head)
{
	t_list	*first;

	first = head->data->env->next;
	while (first)
	{
		if (first->value != NULL)
			ft_printf("%s=%s\n", first->key, first->value);
		first = first->next;
	}
	g_exit_status = 0;
}

void	unset(t_head *head, char *key)
{
	if (key != NULL)
		remove_node(&(head->data->env->next), key);
	g_exit_status = 0;
}
