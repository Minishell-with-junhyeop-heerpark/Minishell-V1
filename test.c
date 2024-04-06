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

#include "inc/minishell.h"

char	*get_pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * 1024);
	if (getcwd(cwd, 1024) == NULL)
		perror_exit("getpwd() error");
	return (cwd);
}

void	add_desktoppath(void)
{
	char	*now_path;
	char	*desktop_path;
	char	*res;
	char	*path = "~/hello/world";
	int		i;

	now_path = get_pwd();
	desktop_path = (char *)malloc(sizeof(char) * 100);
	printf("get success: %s\n", now_path);
	i = 0;
	while (now_path[i])
	{
		if (now_path[i] == '/')
		{
			if (strncmp(&now_path[i], "/Desktop/", 9) == 0)
				break ;
		}
		i++;
	}
	ft_strlcpy(desktop_path, now_path, i + 9);
	printf("desktop_path: %s\n", desktop_path);
	res = ft_strjoin(desktop_path, ++path);
	printf("res: %s\n", res);
}

int  main() {
    // char *const argv[] = {"co_minishell/minishell", NULL};
    // char *const envp[] = {NULL};
    // execve("co_minishell/minishell", argv, envp);
	add_desktoppath();
    return 0;
}
