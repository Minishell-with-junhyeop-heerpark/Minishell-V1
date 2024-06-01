/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyeop <junhyeop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:33:50 by junhyeop          #+#    #+#             */
/*   Updated: 2024/06/01 15:59:57 by junhyeop         ###   ########.fr       */
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

typedef struct s_flag
{
	int	quote;
	int	dquote;
	int	pipe;

}	t_flag;

typedef struct s_parse
{
	t_flag	flag;
	int		start;
	int		i;
}	t_parse;

typedef struct s_token
{
	char			*cmd;
	int				redir_flag;
	int				replace_flag;
	int				quote_flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

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
	char	*heredoc_filename;
	char	*cmd;
	char	*exec_path;
	char	**exec_cmd;
	t_list	*env;
}	t_process;

typedef struct s_data //heredoc 파일 경로 여기로 옮기기.
{
	int		original_stdin;
	int		original_stdout;
	int		**pipes;
	char	*home;
	char	**envp;
	t_list	*env;
}	t_data;

typedef struct s_split_var {
	t_token	*lst;
	char	*backup;
	int		i;
	int		flag;
	int		start;
	int		quote;
	int		dquote;
}	t_split_var;

typedef struct s_head {
	int				size;
	int				get_error;
	struct s_list	*top;
	t_data			*data;
	t_process		**processes;
}	t_head;

typedef struct s_value_var
{
	int	n;
	int	i;
	int	s;
}	t_value_var;

int			g_exit_status;
int			check_white_space(char *str);

//parsing func
void		error_msg(int type);
void		add_cmd(t_head *head, char *line, int pipe_flag);
void		add_token(t_token **lst, char *cmd);

char		*make_cmd(char *cmd, t_split_var *sv, char q);
t_token		*make_token(char *command);
t_head		*init_head(char **envp, int argc, char **argv);
t_token		*token_new(char *command, int flag, int dquote_flag);
void		void_argument(int argc, char **argv);
t_list		*cmd_list_new(char *command);
void		ft_lst_add(t_head *head, t_list *new);
void		ft_token_add(t_token **lst, t_token *new);
char		**split_pipe(char const *s);
t_token		*split_space(char *s, char space);
void		free_list(t_head *head, char *str);
void		clear(t_head *head, char *str);
int			parse(char *str, t_head *head);

//exe func

	//exe_parsing.c
char		*get_envpath(char **envp);

	//exe_utils.c
void		perror_exit(char *msg);
void		free_splited(char **splited);
int			**make_pipe(int child_num);
void		free_pipe(int **pipe, int child_num);

	//pipe_control
void		wait_process(int child_num);
void		first_child(t_head *head, int **pipes, char **envp, int i);
void		last_child(t_head *head, int **pipes, char **envp, int i);
void		mid_child(t_head *head, int **pipes, char **envp, int i);
void		parent(int **pipes, int i);
void		close_all_pipes(int **pipes, int n);

	//get_fd
int			check_redir_heredoc(t_process *process);
int			get_infile(t_head *head, char *file_name);
int			get_heredoc(t_head *head, t_process *process, char *limiter);
int			get_outfile(t_head *head, char *file_name);
int			get_append(t_head *head, char *file_name);
void		init_fd(t_process *process);

	//here_doc
void		kill_heredoc(t_head *head);
char		*get_temp_name(void);
void		make_infile(char *limiter, char *file_name);
void		make_temp(char *limiter, char *file_name);

	//list_to_processes
void		fill_elem(t_head *head, t_token *temp, \
					t_process *process, char **cmd);
void		set_fd(t_head *head, t_process *process, \
					char *file_name, int redir_flag);
void		close_unused_input(t_process *process);
void		close_unused_output(t_process *process);
char		*getkey(char *str);
char		*env_find_value(char *key, t_list *envp);
void		replace_value(char *new_cmd, int *ind, char *value);
char		*replace_cmd(char *cmd, char *key, char *value, int *ind);
char		*apply_env(char *cmd, t_list *env, int *ind);
char		*apply_exit_status(char *cmd, int *ind);
void		check_env(t_token *token, t_process *process);
void		concat_cmd(t_token *temp, t_process *process, \
			char **cmd, char **str);
int			no_cmd(t_head *head, t_process *process);
void		set_builtin(t_head *head, t_process *process, char **exec_cmd);
void		set_exec(t_head *head, t_process *process, char **path, int i);
int			get_redir_flag(char	*token);
void		set_process(t_head *head, t_process *process, char **path);
void		init_process(t_process *process);
t_process	*get_process(t_head *head, t_list *line, char **path);

	//processes_exe
void		run_cmd(t_head *head, char **envp, int i);
void		get_processes(t_head *head, char **envp);
void		set_inout(t_process *process, int **pipes, int i, int close_sig);
void		start_process(t_head *head, char **envp);
void		start_processes(t_head *head, char **envp, int **pipes);
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
void		sig_handler(int signo);
void		set_signal(void);
void		temi_print_off(void);
void		temi_print_on(void);
void		set_signal_heredoc(void);
void		do_sigint_heredoc(int signum);
void		exit_signal(void);

// ft_exit.c
int			ft_exit(char **exec_cmd);

// ft_export.c
void		ft_export(t_head *head, char **exec_cmd);
void		export_update(t_head *head, t_list **lst, char *key, char *value);
int			get_op(char *cmd);
void		ft_export_ext(t_head *head, t_list *env, int op);

void		export_add_prev(t_list **lst, t_list *new, t_list **top);
void		sorting(t_list *t_env, t_list **top);
void		sort_list(t_list *env, t_list **top);
void		show_export(t_head *head);
char		*export_strjoin(char *s1, char *s2);

void		free_show_list(t_list **top);
void		key_error(char *key);
int			key_validate(char *key);
char		*export_getkey(char *cmd, int *op);
char		*export_getvalue(char *cmd);

// error.c
void		print_error(char *cmd, char *input, char *msg, int exit_status);
void		print_bash_error(char *input, char *msg, int exit_status);

//free.c
void		clear_processes(t_head *head);

// utils2.c
void		init_parse(t_parse *p);
int			s_quote_check(char c, t_split_var *flag);
int			s_dquote_check(char c, t_split_var *flag);
int			set_len(char *str, int i, char q);

// utils3.c
void		set_home(t_head *head);
void		temi_print_off(void);
void		set_signal_heredoc(void);
void		set_signal_origin(void);
void		do_sigint_heredoc(int signum);
void		exit_signal(void);
void		sig_handler(int signo);
void		set_signal(void);
void		temi_print_on(void);
void		export_update_free(char *env_value, char *value, char *key);
int			key_check(char c);

// ft_cd.c
void		cd(t_head *head, char *dir);
void		change_env(t_head *head);
void		change_pwd(t_list *env, char *cwd);


#endif