/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:27:44 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/21 22:55:04 by junhyeop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include "libft/libft.h"

# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include <unistd.h>
# include <termios.h>

typedef struct s_token
{
	char			*cmd;
	int				redir_flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_flag
{
	int	quote;
	int	dquote;
	int pipe;

}	t_flag;

typedef struct s_split_list 
{
	char			*cmd;
	struct s_list	*next;
	struct s_list	*prev;
}	t_split_list;

typedef struct s_list
{
	t_token			*cmd;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_head {
	int				size;
	struct s_cmd	*top;
}	t_head;

void	error_msg(int type);

void	add_token(t_token **lst, char *cmd);
t_token	*make_token(char *command);


t_head	*list_init();
t_list	*cmd_list_new(char *command);
void	ft_lstadd_back(t_head *head, t_list *new);

char	**split_pipe(char const *s);
t_token	*split_space(char *s, char space);	// pipe 단위로 나눈 것 -> 공백 단위로 나눔

// void	make_token(t_head *head);

void	parse(char *str, t_head *head);
#endif