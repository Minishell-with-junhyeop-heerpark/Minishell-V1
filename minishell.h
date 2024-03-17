/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:27:44 by junhyeop          #+#    #+#             */
/*   Updated: 2024/03/17 08:09:43 by junhyeop         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>

void	parse(char *str, t_head *head);

typedef struct s_token
{
	char	*cmd;
	char	redir_flag;
}	t_token;

typedef struct s_falg
{
	int	quote;
	int	dquote;
	int pipe;

}	t_falg;

typedef struct s_list
{
	char			*cmd;
	struct s_list	*next;
}	t_list;

typedef struct s_head {
	int				size;
	struct s_cmd	*top;
}	t_head;

void	error_msg(int type);

t_head	*list_init();
t_list	*ft_lstnew(char *cmd);


#endif