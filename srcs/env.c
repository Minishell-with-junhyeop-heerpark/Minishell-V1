/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:07:00 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/28 22:32:30 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_env(t_list **head, char **envp)
{
	int		n;
	int		i;
	char	*key;
	char	*value;

	n = 0;
	while (envp[n])
	{
		i = 0;
		while (envp[n][i])
		{
			if (envp[n][i] == '=')
			{
				key = ft_substr(envp[n], 0, i);
				value = ft_substr(envp[n], i + 1, 2147483647);
				lstadd_back(head, lst_new(key, value));
				// printf("%s = %s\n", key, value);
			}
			i++;
		}
		// printf("%s\n", envp[n]);
		n++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*head;

	set_env(&head, envp);
	lst_print(head);
}