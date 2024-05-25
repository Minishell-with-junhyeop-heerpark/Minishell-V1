/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpwdcd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:27:15 by heerpark          #+#    #+#             */
/*   Updated: 2024/05/25 17:33:57 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//pwd 마지막에 개행을 넣어 말어 (현재 x)
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

void	cd(t_head *head, char *dir)
{
	if (dir == NULL)
	{
		if (chdir(head->data->home) == -1)
		{
			g_exit_status = 1;
			ft_printf("bash: cd: %s: can't implement cd\n", dir);
		}
	}
	else
	{
		if (chdir(dir) == -1)
		{
			g_exit_status = 1;
			ft_printf("bash: cd: %s: can't implement cd\n", dir);
		}
	}
}
