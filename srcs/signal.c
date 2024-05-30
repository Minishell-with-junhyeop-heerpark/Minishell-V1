/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:06:54 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/30 14:48:35 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\n", STDERR);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 1;
		}
		else
			ft_putstr_fd("\n", STDOUT);
	}
}

void	set_signal(void)
{
	temi_print_off();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	temi_print_on(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
}
