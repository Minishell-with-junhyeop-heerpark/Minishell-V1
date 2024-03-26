/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:27:15 by heerpark          #+#    #+#             */
/*   Updated: 2024/03/26 21:34:11 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
// echo pwd cd export unset env exit

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

//pwd 마지막에 개행을 넣어 말어 (현재 x)
void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, strlen(cwd));
	}
	else
	{
		perror_exit("getcwd() error");
	}
	exit (0);
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(0);
}

void	run_builtin(char *cmd, char **envp)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return ;
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return ;
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return ;
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return ;
	else if (ft_strncmp(cmd, "env", 4) == 0)
		env(envp);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return ;
	else
		printf("it is not built in cmd\n");
}
