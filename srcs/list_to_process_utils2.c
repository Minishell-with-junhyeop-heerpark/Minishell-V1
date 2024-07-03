/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:53:55 by heerpark          #+#    #+#             */
/*   Updated: 2024/07/03 21:31:23 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

char	*getkey(char *str)
{
	char	*dest;
	int		n;
	int		i;

	n = 0;
	i = 0;
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

char	*add_env(char *cmd, t_list *env, int *ind, int *cnt)
{
	char	*changed;
	char	*key;
	char	*value;

	key = getkey(&cmd[*ind + 1]);
	value = env_find_value(key, env);
	if (!value)
		error_msg(0, NULL);
	changed = replace_cmd(cmd, key, value, ind);
	*ind = *ind + (ft_strlen(value) - 1 - ft_strlen(key));
	if (*ind < 0)
		*ind = 0;
	*cnt = *cnt + (ft_strlen(value) - 1 - ft_strlen(key));
	free(key);
	free(value);
	free(cmd);
	return (changed);
}
