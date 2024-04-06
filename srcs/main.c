/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/04/06 14:29:11 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gcc testsignal.c -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include

void	sig_handler(int signo)
{
	// ^C 출력할지말지
    if (signal == SIGINT)
    {
        //printf("\033[K"); 지워버리는 것을 원하지는 않았음.
        printf("minishell$ \n");
    }
 
    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    // display();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

    char			*str;
    struct termios	term;
	t_head			*head;

	sig = -1;
    // 터미널 세팅
    // tcgetattr(STDIN_FILENO, &term);
    // term.c_lflag &= ~(ECHOCTL);
    // tcsetattr(STDIN_FILENO, TCSANOW, &term);

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	tcsetattr(1, 0, &term);  // 변경한 term 설정을 현재 터미널에 적용
    // 시그널 세팅
	
    setting_signal();
	head = init_head(envp);
	printf("Welcome to minishell!\n");
    while (1)
    {

        str = readline("minishell$ ");
		printf("input!!\n");
        if (!str)
        {
            //  minishell$ exit
            printf("\033[1A");
            printf("\033[10C");
            printf(" exit\n");
            exit(-1);
        }
        else if (*str == '\0')
        {
            free(str);
        }
        else
        {
            add_history(str);
			parse(str, head);
			// make_token(cmd_list);
            // printf("%s\n", str);
			exe(head, envp);
			free_list(head);
            free(str);
        }
    }
    /* 함수종료 */
    return (0);
}

//file descriptor 싹다 닫아주는 함수 만드는 것도 좋을듯.