#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int         main(void)
// {
//     int     errno = 0;
//     char    *error_message;

//     printf("< errno와 에러메세지 목록 >\n");
//     for (errno = 0; errno < 108; errno++)
//     {
//         error_message = strerror(errno);
//         printf("%d. %s\n", errno, error_message);
//     }
// 	// printf("\a");
//     return (0);
// }

#include <stdio.h>
#include <unistd.h>

// char	*get_pwd(void)
// {
// 	char	*cwd;

// 	cwd = (char *)malloc(sizeof(char) * 1024);
// 	if (getcwd(cwd, 1024) == NULL)
// 		perror_exit("getpwd() error");
// 	return (cwd);
// }

void	cd(char *dir)
{
	printf("im in cd, dir: %s\n", dir);
	if (chdir(dir) == -1)
		perror("cd");
}

int  main() {
    // char *const argv[] = {"co_minishell/minishell", NULL};
    // char *const envp[] = {NULL};
    // execve("co_minishell/minishell", argv, envp);
	cd("~");
    return 0;
}
