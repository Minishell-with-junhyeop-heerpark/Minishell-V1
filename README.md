# 🚧 진행중..
# heerpark To do list

<signal>
signal처리. 자식프로세스에서 ctrl+c 로 종료되는 경우도 생각하자. c.f. WTERMSIG(status)
echo $? 에서 ? 전역변수로 치환되게하기 !!.
https://tempdev.tistory.com/42

<process>
echo ehco a | ./minishell 에서 파이프 이후 프로세스 실행되는거 종료하기.

<heredoc>
heredoc 자식프로세스만들어서 받기. (heredoc process 처리할때 잘 안되면 readline 사용.)
kill heredoc 실행 경로, 명령어 t_data 내의 변수로 변경.

<pipe, fd>
프로세스 종료 후에 모든 파이프, 모든 fd 닫아주기. !!!!!