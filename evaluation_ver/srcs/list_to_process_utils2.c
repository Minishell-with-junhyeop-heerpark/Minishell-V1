/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeong <junhyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/07 18:35:02 by junhyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_find_value(char *key, t_list *envp)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (ft_strdup(""));
}

void	replace_value(char *new_cmd, int *ind, char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		new_cmd[*ind] = value[i];
		*ind += 1;
		i++;
	}
}

char	*replace_cmd(char *cmd, char *key, char *value, int *ind)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - \
	(ft_strlen(key) + 1) + ft_strlen(value) + 1));
	while (i < *ind)
		new_cmd[j++] = cmd[i++];
	replace_value(new_cmd, &j, value);
	i += ft_strlen(key) + 1;
	while (cmd[i])
		new_cmd[j++] = cmd[i++];
	new_cmd[j] = 0;
	return (new_cmd);
}

char	*add_env(char *cmd, t_list *env, int *ind, int origin)
{
	char	*changed;
	char	*key;
	char	*value;

	(void) origin;
	key = getkey(&cmd[*ind + 1]);
	value = env_find_value(key, env);
	if (!value)
		error_msg(0, NULL);
	changed = replace_cmd(cmd, key, value, ind);
	*ind = *ind + (ft_strlen(value) - 1 - ft_strlen(key));
	if (*ind <= 0)
	{
		*ind = 0;
		if (cmd[0] == '\"')
			*ind = 1;
	}
	free(key);
	free(value);
	free(cmd);
	return (changed);
}
