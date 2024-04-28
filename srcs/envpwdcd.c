/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpwdcd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:27:15 by heerpark          #+#    #+#             */
/*   Updated: 2024/04/28 16:05:20 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//pwd 마지막에 개행을 넣어 말어 (현재 x)
void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror_exit("pwd() error");
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
}

void	unset(t_head *head, char *key)
{
	remove_node(&(head->data->env->next), key);
}

void	cd(t_head *head, char *dir)
{
	if (dir == NULL)
	{
		if (chdir(head->data->home) == -1)
			perror_exit("cd");
	}
	else
	{
		if (chdir(dir) == -1)
			perror_exit("cd");
	}
}
