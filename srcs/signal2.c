/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:03:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 20:06:02 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temi_print_off()
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, do_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_origin(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	do_sigint_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR);
	exit (1);
}

void	exit_signal()
{
	ft_printf("\033[1A");
	ft_printf("\033[10C");
	ft_printf(" exit\n");
	exit(-1);
}
