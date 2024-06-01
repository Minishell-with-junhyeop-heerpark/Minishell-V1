/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:59:21 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/02 00:02:24 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_list *env, char *cwd)
{
	char	*tmp;

	if (cwd == NULL)
		error_msg(0, NULL);
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			tmp = env->value;
			env->value = cwd;
			free(tmp);
			return ;
		}
		env = env->next;
	}
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
		error_msg(0, NULL);
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
