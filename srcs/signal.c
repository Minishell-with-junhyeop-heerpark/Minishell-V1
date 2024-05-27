/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:06:54 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/27 21:43:15 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	//-1 : 자식 프로세스를 기다림.
	//status : 자식 프로세스가 종료되면 자식 pid값이 할당 됨.
	//WNOHANG : 자식 프로세스가 종료되지 않아서 pid를 회수할 수 없는 경우 반환값으로 0을 받음.
	if (signo == SIGINT){
		if (pid == -1)
		//pid == -1 : 자식 프로세스가 없는 경우
		{
			ft_putstr_fd("\n", STDERR); // 줄바꿈 출력
			rl_on_new_line(); // 커서가 다음줄로 옮겨간것을 readline에 적용
			rl_replace_line("", 0); // 현재 버퍼를 비워줌
			rl_redisplay(); // readline 메시지를 다시 출력
			g_exit_status = 1;
		}
		else
			ft_putstr_fd("\n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
	}

} 

void	set_signal()
{
	temi_print_off();
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}

void	temi_print_on()
{
	struct termios term;
	
	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	tcsetattr(1, 0, &term);  // 변경한 term 설정을 현재 터미널에 적용
    // 시그널 세팅
	
}
