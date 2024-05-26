# 🚧 진행중..
# heerpark To do list

<signal>

1. signal 종료랑 일반 종료코드 일단 인식되긴함. 근데 WIFSIGNALED 타고 들어와서 WTERMSIG되는건
"kill -TERM 자식pid"로 시그널 줄때만 인식돼서 확인필요함.(signal로 죽이는 거 뭐뭐있는지 알아보자)

2. echo $? 에서 ? 전역변수로 치환되게하기. -> "", ''에서 치환하는건 준형이 코드에서 추가해야할듯
echo hi$?hi 는 중간에 에러코드로 치환되는데 echo hi$PATHhi는 hihi로 무시되고 출력됨. 알아보자...

참고: https://tempdev.tistory.com/42

<process> - CLEAR
echo ehco a | ./minishell 에서 파이프 이후 프로세스 실행되는거 종료하기.
-> wait pid로 숫자 계속 세면서 stop되어있으면 kill을 줘야하나...?

<temi>
자식프로세스에서 ctrl-c 받는거 처리할라면 temi 켜놔야함.
heredoc수정할때도 추가하면 좋을듯

<pipe, fd>
프로세스 종료 후에 모든 파이프, 모든 fd 닫아주기. !!!!!


<note book compile>
For compilers to find readline you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/readline/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/readline/include"

<found error>

exec_cmd = ft_split(process->cmd, ' ');
if (exec_cmd[0] == NULL)
{
	unlink(process->heredoc_filename);
	perror_exit("no cmd");
}

<< heredoc만 입력하면 bash에서는 그냥 입력받고 끝나는데 내꺼에서는 입력받고 no cmd에러 뜨면서 튕김. 체크하자 !!.

<heredoc>
cat << end | cat << quit
이런식으로 입력할 때 파이프로 넘어온 내용보다 자식프레스의 heredoc의 내용이 우선시되어 출력됨.
확인해보자.
heredoc 경로를 temp 로 할지 현재 폴더로 할지 정하기.

<0515 발견된 에러들>
1. builtin exit status 세팅 -O
2. echo "a           a" 케이스. 해결법 -> char **cmd를 echo\na               a\n 이런식으로 개행을 cmd구분자로 두고 split('\n')
3. env list랑 parsing list 분리.


# 루틴
1. whonang으로 자식프로세스 대기중인거 체크하기. - clear
2. heredoc 자식 프로세스에서 받고 처리하기 - clear
3. 코드 구조랑 norm 맞추면서 leak, fd 처리하기.



* execve에 넣는 envp를 업데이트 해줘야할지 말아야할지 정하기 업데이트 한다면 update_envp()를 사용하자.
* 파싱 중간에 '들어오면 미니쉘 먹통됨 ex) echo', 다른 케이스들도 있을듯
* echo echo a | ./minishell 케이스에서 자식 프로세스 종료 안되는거 check


zzz