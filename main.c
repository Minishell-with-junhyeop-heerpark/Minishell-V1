/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:10:35 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/21 22:00:00 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// gcc testsignal.c -lreadline -L/Users/sham/.brew/opt/readline/lib -I/Users/sham/.brew/opt/readline/include

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        //printf("\033[K"); 지워버리는 것을 원하지는 않았음.
        printf("minishell$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
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
	t_head			*cmd_list;

    // 터미널 세팅
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // 시그널 세팅
	
    setting_signal();
	cmd_list = list_init();
	printf("Welcome to minishell!\n");
    while (1)
    {
        str = readline("minishell$ ");
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
			parse(str, cmd_list);
			// make_token(cmd_list);
            // printf("%s\n", str);
            free(str);
        }
    }
    /* 함수종료 */
    return (0);
}