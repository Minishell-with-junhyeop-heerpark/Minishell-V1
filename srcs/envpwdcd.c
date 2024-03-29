/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpwdcd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:27:15 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/29 09:44:55 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//pwd 마지막에 개행을 넣어 말어 (현재 x)
void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
	}
	else
	{
		perror_exit("getcwd() error");
	}
}

void	env(t_head *head)
{
	t_list	*first;

	first = head->data->env;
	while (first)
	{
		ft_printf("%s=%s\n", first->key, first->value);
		first = first->next;
	}
}

void	cd(char *dir)
{
	printf("im in cd, dir: %s\n", dir);
	if (chdir(dir) == -1)
		perror_exit("cd");
}
