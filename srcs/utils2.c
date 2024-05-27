/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:54:44 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 19:58:35 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse(t_parse *p)
{
	p->flag = (t_flag){0, 0, 1};
	p->i = 0;
	p->start = 0;
}

int	is_empty(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	s_quote_check(char c, t_split_var *flag)
{
	if (c == '\'')
	{
		flag->quote = 1;
		flag->dquote = 0;
	}
	else if (c == '\"')
	{
		flag->quote = 0;
		flag->dquote = 1;
	}
	else
		return (0);
	return (1);
}

int	s_dquote_check(char c, t_split_var *flag)
{
	if (flag->dquote == 1)
		return (1);
	if (c == '\"' && flag->dquote == 0)
	{
		flag->dquote = 1;
		return (1);
	}
	if ((c == '\"') && flag->dquote == 1)
	{
		flag->dquote = 0;
		return (0);
	}
	return (flag->dquote);
}

int	set_len(char *str, int i, char q)
{
	i++;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (-1);
}
