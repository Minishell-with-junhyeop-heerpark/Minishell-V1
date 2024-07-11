/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_process_utils6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:08:47 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/09 20:19:44 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*t_replace_cmd(char *cmd, char *key, char *value, int *ind)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - \
	(ft_strlen(key)) + ft_strlen(value) + 1));
	if (!new_cmd)
		error_msg(0, NULL);
	while (i < *ind)
		new_cmd[j++] = cmd[i++];
	replace_value(new_cmd, &j, value);
	i += 1;
	while (cmd[i])
		new_cmd[j++] = cmd[i++];
	new_cmd[j] = 0;
	return (new_cmd);
}

char	*tilde_parse(char *cmd, t_list *env, int *ind)
{
	char	*changed;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = ft_strdup("~");
	value = env_find_value("HOME", env);
	if (!value)
		error_msg(0, NULL);
	changed = t_replace_cmd(cmd, key, value, ind);
	*ind = i;
	free(key);
	free(value);
	free(cmd);
	return (changed);
}

int	check_t(char *str, int ind)
{
	int	i;

	i = ind;
	if (str[i] != '~' || i != 0)
		return (0);
	if (str[i + 1] != 0 && str[i + 1] != '/')
		return (0);
	return (1);
}
