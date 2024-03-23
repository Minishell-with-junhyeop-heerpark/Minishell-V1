#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_token
{
	char			*cmd;
	int				redir_flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_list
{
	t_token			*cmd;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_head {
	int				size;
	struct s_list	*top;
}	t_head;

void	error_msg(int type);
void	ft_lst_add(t_head *head, t_list *new);
t_list	*cmd_list_new(t_token *t);
t_token	*token_new(char *command, int flag);
void	ft_token_add(t_token **lst, t_token *new);
t_head	*init_head();
void	ft_putstr_fd(char *s, int fd);



#endif