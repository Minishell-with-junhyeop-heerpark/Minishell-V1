/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heerpark <heerpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:33:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/05/15 16:22:04 by heerpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>

# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

int g_exit_status;

typedef struct s_flag
{
	int	quote;
	int	dquote;
	int pipe;

}	t_flag;

typedef struct s_token
{
	char			*cmd;
	int				redir_flag;
	int				replace_flag;
	int				quote_flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_list
{
	t_token			*token;
	char			*key;
	char			*value;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_process
{
	int		re_infile_fd;
	int		re_outfile_fd;
	int		re_append_fd;
	int		heredoc_fd;
	int		is_built;
	char	*heredoc_filename;
	char	*cmd;
	char	*exec_path;
	char	**exec_cmd;
	char	*builtin_cmds;
	t_list	*env;
}	t_process;

typedef struct s_data //heredoc 파일 경로 여기로 옮기기.
{
	char			**exec_rm_cmd;
	char			*exec_rm_path;
	int				original_stdin;
	int				original_stdout;
	char			**envp;
	char			*home;
	t_list			*env;
}	t_data;

typedef struct s_head {
	int				size;
	int				get_error;
	char			**exec_rm_cmd;
	char			*exec_rm_path;
	struct s_list	*top;
	t_data			*data;
	t_process		**processes;
}	t_head;

//parsing func
void		error_msg(int type);

void		add_cmd(t_head *head, char *line, int pipe_flag);
void		add_token(t_token **lst, char *cmd);

t_token		*make_token(char *command);
t_head		*init_head(char **envp);
t_token		*token_new(char *command, int flag, int dquote_flag);

t_list		*cmd_list_new(char *command);
void		ft_lst_add(t_head *head, t_list *new);
void		ft_token_add(t_token **lst, t_token *new);

char		**split_pipe(char const *s);
t_token		*split_space(char *s, char space);	// pipe 단위로 나눈 것 -> 공백 단위로 나눔

void		free_list(t_head *head);
void		parse(char *str, t_head *head);

//exe func

	//exe_parsing.c, exe_parsing2.c)
char		**get_exec_paths(char **envp, char **cmds, int path_size);
char		*get_envpath(char **envp);
char		**get_cmd_head(char **argv, int start_idx, int end_idx);
char		***make_cmds(char **argv, int start_idx, int end_idx);
void		free_cmds(int cmds_size, char ***cmds);

void		free_splited(char **splited);
int			**make_pipe(int child_num);
void		free_pipe(int **pipe, int child_num);
void		perror_exit(char *msg);

	//pipe_control
void		wait_process(int child_num);
void		first_child(t_head *head, int **pipes, char **envp, int i);
void		last_child(t_head *head, int **pipes, char **envp, int i);
void		mid_child(t_head *head, int **pipes, char **envp, int i);
void		parent(int **pipes, int i);
void		close_all_pipes(int **pipes, int n);

	//get_fd
int			check_redir_heredoc(t_process *process);
int			get_infile(char	*file_name);
int			get_heredoc(t_process *process, char *limiter);
int			get_outfile(char *file_name);
int			get_append(char *file_name);
void		init_fd(t_process *process);

	//here_doc
void		kill_heredoc(t_head *head, char **envp);
char		*get_temp_name(void);
void		make_infile(char *limiter, char *file_name);
void		make_temp(char *limiter, char *file_name);

	//list_to_processes_utils
void		fill_elem(t_token *temp, t_process *process, char **cmd, int flag);
void		set_fd(t_process *process, char *file_name, int redir_flag);
int			get_redir_flag(char	*token);
void		set_process(t_head *head, t_process *process, char **path);
t_process	*get_process(t_head *head, t_list *line, char **path);

	//processes_exe
void		get_processes(t_head *head, char **envp);
void		set_inout(t_process *process, int **pipes, int i, int close_sig);
void		start_process(t_head *head, char **envp);
void		start_processes(t_head *head, char **envp, int **pipes, int n);
void		exe(t_head *head, char **envp);

	//builtin.c
int			is_builtin(char **exec_cmd);
void		run_builtin(t_head *head, char **exec_cmd);
int			is_exit(char **exec_cmd);

	//envpwd.c ft_echo.c
void		env(t_head *head);
void		pwd(void);
void		cd(t_head *head, char *dir);
void		unset(t_head *head, char *key);
void		ft_echo(char **exec_cmd);

	//list_control.c
t_list		*lst_new(char *key, char *value);
void		lstadd_back(t_list **lst, t_list *new);
char		*remove_node(t_list **lst, char *key);
void		lst_clear(t_list **lst);
void		lst_print(t_list *head);
void		get_node_value(t_list *env, t_token *token);

	//env_control.c
void		set_env(t_list **head, char **envp);
char		*get_envp_line(t_list *head);
void		update_envp(t_head *head);

	//file_exe.c
int			is_filepath(char **exec_cmd);
char		*get_pwd(void);
void		add_homepath(t_head *head, char **exec_cmd, int only_home);

	//ft_echo.c
void		ft_echo(char **exec_cmd);

	// signal.c
void	sig_handler(int signo);
void	set_signal();
void	temi_print_off();
void	temi_print_on();
void	set_signal_heredoc(void);
void	do_sigint_heredoc(int signum);
void	exit_signal();

// ft_exit.c
int	ft_exit(char **exec_cmd);

typedef struct s_split_var {
	t_token	*lst;
	char	*backup;
	int		i;
	int		flag;
	int		start;
	int		quote;
	int		dquote;
}	t_split_var;

#endif