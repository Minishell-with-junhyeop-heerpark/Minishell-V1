/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:29 by junhyeop          #+#    #+#             */
/*   Updated: 2024/07/03 16:20:02 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_check(char c, t_flag *flag)
{
	if (flag->dquote == 1)
		return (flag->quote);
	if (c == '\'' && flag->quote == 0)
		return (1);
	if ((c == '\'') && flag->quote == 1)
		return (0);
	return (flag->quote);
}

int	dquote_check(char c, t_flag *flag)
{
	if (flag->quote == 1)
		return (flag->dquote);
	if (c == '\"' && flag->dquote == 0)
		return (1);
	if ((c == '\"') && flag->dquote == 1)
		return (0);
	return (flag->dquote);
}

int	check_quote(int dq, int q, t_head *head)
{
	if (!dq && !q)
		return (0);
	head->get_error = 3;
	return (1);
}

void	add_cmd(t_head *head, char *line, int pipe_flag)
{
	int		i;
	char	*command;

	(void)pipe_flag;
	i = 0;
	if (line[i] == ' ')
		i++;
	command = ft_strdup(&line[i]);
	if (!command)
		error_msg(0, NULL);
	if (check_white_space(command))
	{
		if (pipe_flag && line[i + 1] == '|')
			head->get_error = 4;
		else if (pipe_flag)
			head->get_error = 2;
		else
			head->get_error = 3;
		free(command);
		return ;
	}
	ft_lst_add(head, cmd_list_new(command, head));
	free(command);
}

int	parse(char *line, t_head *head)
{
	t_parse	p;

	init_parse(&p);
	while (1)
	{
		p.flag.quote = quote_check(line[p.i], &p.flag);
		p.flag.dquote = dquote_check(line[p.i], &p.flag);
		if (line[p.i] == '\0' || (line[p.i] == '|' \
		&& (p.flag.quote == 0 && p.flag.dquote == 0)))
		{
			if (line[p.i] == '\0')
				p.flag.pipe = 0;
			line[p.i] = '\0';
			if (check_quote(p.flag.dquote, p.flag.quote, head))
				return (0);
			add_cmd(head, &line[p.start], p.flag.pipe);
			p.start = p.i + 1;
			if (head->get_error)
				return (0);
			if (p.flag.pipe == 0)
				break ;
		}
		p.i++;
	}
	return (1);
}
