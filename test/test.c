#include "test.h"

void	ft_lst_add(t_head *head, t_list *new)
{
	t_list	*tmp;

	head->size = head->size + 1;
	tmp = head->top;
	if (tmp == NULL)
	{
		head->top = new;
		return ; 
	}
	else if (tmp == NULL && new == NULL)
	{
		error_msg(1);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_list	*cmd_list_new(t_token *t)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		error_msg(1);
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->cmd = t;
	return (newnode);
}
t_token	*token_new(char *command, int flag)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		error_msg(1);
	new->prev = NULL;
	new->next = NULL;
	new->cmd = command;
	new->redir_flag = flag;
	return (new);
}

void	ft_token_add(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ; 
	}
	if (tmp == NULL && new == NULL)
		error_msg(1) ;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_head	*init_head()
{
	t_head	*head;

	head = (t_head *)malloc(sizeof(t_head));
	if (!head)
		error_msg(1);
	head->top = NULL;
	head->size = 0;
	return (head);
}

void	error_msg(int type)
{
	if (type == 1)
		ft_putstr_fd("malloc error\n", 2);
	exit(1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return ((size_t)n);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(s1);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == 0)
		return (0);
	while (s1[i] != 0)
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}


int main()
{
	t_head *head = init_head();

	t_token *token1 = NULL;
	ft_token_add(&token1, token_new(ft_strdup("echo"), 0));
	ft_token_add(&token1, token_new(ft_strdup("hello"), 0));	
	ft_token_add(&token1, token_new(ft_strdup(">"), 1));
	ft_token_add(&token1, token_new(ft_strdup("a"), 0));
	ft_token_add(&token1, token_new(ft_strdup("echo"), 0));

	t_token *token2 = NULL;
	ft_token_add(&token2, token_new(ft_strdup("echo"), 0));
	ft_token_add(&token2, token_new(ft_strdup("hi"), 0));

	t_token *token3 = NULL;
	ft_token_add(&token3, token_new(ft_strdup("cat"), 0));
	ft_token_add(&token3, token_new(ft_strdup(">"), 1));
	ft_token_add(&token3, token_new(ft_strdup("outfile"), 0));

	ft_lst_add(head, cmd_list_new(token1));
	ft_lst_add(head, cmd_list_new(token2));
	ft_lst_add(head, cmd_list_new(token3));

	printf("%s\n", head->top->cmd->next->next->cmd);
	return (0);
}