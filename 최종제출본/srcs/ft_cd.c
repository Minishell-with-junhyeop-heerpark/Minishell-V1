/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:59:21 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 21:18:49 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_list *env, char *cwd)
{
	char	*tmp;
	int		find;

	find = 0;
	if (cwd == NULL)
		error_msg(0, NULL);
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			find = 1;
			tmp = env->value;
			env->value = cwd;
			free(tmp);
			return ;
		}
		env = env->next;
	}
	if (find == 0)
		free(cwd);
}

void	change_env(t_head *head)
{
	char	cwd[1024];
	t_list	*env;

	env = head->data->env->next;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		change_pwd(env, ft_strdup(cwd));
	}
	else
		ft_printf("getcwd: cannot access directories\n");
}

void	cd(t_head *head, char *dir)
{
	int		tmp;

	if (dir == NULL)
	{
		tmp = chdir(head->data->home);
		if (tmp == -1)
		{
			g_exit_status = 1;
			printf("minishell: cd: %s: can't implement cd\n", dir);
		}
		change_env(head);
	}
	else
	{
		tmp = chdir(dir);
		if (tmp == -1)
		{
			g_exit_status = 1;
			printf("minishell: cd: %s: can't implement cd\n", dir);
		}
		change_env(head);
	}
}
