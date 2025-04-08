/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:06 by aledos-           #+#    #+#             */
/*   Updated: 2025/04/04 13:00:05 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include "../lib/libft/libft.h"

# define PATH_MAX			4096

# define SYNTAX_ERR "minishell: syntax error near unexpected token `newline'\n"

extern volatile sig_atomic_t	g_signal_received;

enum e_cmd_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
};

typedef struct s_command
{
	char				**args;
	char				*input;
	char				*output;
	char				*append;
	char				*heredoc;
	enum e_cmd_type		type;
	struct s_command	*next;
}			t_command;

typedef struct s_expand
{
	char				*result;
	int					i;
	int					j;
	bool				in_s_quote;
}			t_expand;

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
};

typedef struct s_token
{
	char				*content;
	enum e_token_type	type;
	struct s_token		*next;
}			t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}			t_env;

typedef struct s_shell
{
	t_env				*env;
	int					exit_status;
	int					running;
	char				*input;
	int					prev_fd;
	t_token				*tokens;
	t_command			*cmds;
	struct termios		original_termios;
}			t_shell;

// MAIN________________________________________________________________________

void				restore_terminal(t_shell *shell);
void				setup_terminal(t_shell *shell);
void				init_shell(t_shell *shell, char **envp);
int					read_input(t_shell *shell);

// PARSING ____________________________________________________________________

int					parse_input(t_shell *shell);
t_token				*create_token(char *content, enum e_token_type type);
enum e_token_type	get_token_type(char *content);
t_token				*get_token_by_index(t_token *token, int index);
int					add_token(t_shell *shell, char *input, int start, int i);
int					count_tokens(t_token *tokens);
int					valid_tokens(t_shell *shell);
int					parse_tokens(t_shell *shell);
t_expand			*init_expansion(void);
void				expand_variables(t_shell *shell, t_token *token);
void				handle_single_quote(t_expand *exp, char *content);
void				add_to_result(t_expand *exp, char *s);
void				copy_char(t_expand *exp, char *content);
int					build_commands(t_shell *shell);
t_command			*create_command(void);
enum e_cmd_type		get_cmd_type(t_token *token);
int					add_redir(t_command *cmd, t_token *token, t_token *next);
int					has_variable(char *s);
int					has_quote(char *s);
int					is_quote(int c);
int					is_operator(int c);
int					is_space(int c);
int					is_redirection(enum e_token_type type);
int					init_commands(t_shell *shell);
int					count_arguments(t_command *cmd);

// ENVIRONMENT _______________________________________________________________

int					env_list_size(t_shell *shell);
char				*malloc_env_list(t_env *env);
char				**convert_env_list(t_shell *shell);
void				copy_env(char *envp, t_env **head, t_env **tail);
t_env				*load_env(char **envp);
t_env				*find_env_var(t_shell *shell, char *var_name);
t_env				*init_env(char **envp);
void				add_env_variable(t_shell *shell, char *name, char *value);
void				update_pwd_env(t_shell *shell, char *old_pwd);

// BUILTINS___________________________________________________________________

char				*redir_cd_no_arg(t_shell *shell);
char				*redir_cd_tilde(t_shell *shell, t_command *cmd);
char				*redir_cd_dash(t_shell *shell);
char				*redir_cd_path(t_shell *shell, t_command *cmd);
void				print_var_export(t_shell *shell);
void				remove_variable_env(t_shell *shell, char *var_name);
void				print_exit_error(t_shell *shell, char *args);
void				check_valid_exit(t_shell *shell, t_command *cmd);
void				execute_echo(t_command *cmd);
void				execute_cd(t_shell *shell, t_command *cmd);
void				execute_env(t_shell *shell);
void				execute_pwd(void);
void				execute_exit(t_shell *shell, t_command *cmd);
void				execute_export(t_shell *shell, t_command *cmd);
void				execute_unset(t_shell *shell, t_command *cmd);

// REDIRECTIONS_______________________________________________________________

int					redir_input(t_command *cmd);
int					redir_output(t_command *cmd);
int					redir_append(t_command *cmd);
int					read_heredoc(t_command *cmd, char *line, int heredoc_fd[2]);
int					redir_heredoc(t_command *cmd);
int					handle_redirections(t_command *cmd);
void				print_error(const char *file);

//PIPE________________________________________________________________________

void				error_dup2(int fd_1, int fd_2, const char *msg);
void				wait_for_children(t_shell *shell);
void				error_fork(void);
int					create_pipe(int pipe_fd[2]);
void				child_proc(t_shell *shell, t_command *cmd, int pipe_fd[2],
						char **path);
void				check_redir(t_shell *shell, t_command *cmd, int pipe_fd[2],
						char **path);
void				parent_proc(t_shell *shell, t_command *cmd, int pipe_fd[2]);
void				execute_pipe(t_shell *shell);

// EXECUTION__________________________________________________________________

int					is_builtins(t_command *cmd);
void				execute_builtins(t_command *cmd, t_shell *shell);
void				execute_commands(t_shell *shell);
char				**find_path(t_shell *shell);
int					exec_relative_path(t_command *cmd, char **tab_env);
int					exec_path_env(t_command *cmd, char **path, char **tab_env);
int					access_command(t_shell *shell, t_command *cmd, char **path);
void				process_cmd(t_shell *shell, t_command *cmd, char **path);
void				execute_external_command(t_shell *shell, t_command *cmd);
void				execute_builtin_with_redir(t_command *cmd, t_shell *shell);
void				print_cmd_not_found(t_command *cmd);
void				free_child(t_shell *shell, char **path);

// SIGNALS ___________________________________________________________________

void				setup_signals(void);
void				handle_child_exit_status(t_shell *shell, int status);

// TOOLS ______________________________________________________________________

void				free_token(t_token *token);
void				free_tokens(t_token *token);
void				free_command(t_command *cmd);
void				free_commands(t_command *cmd);
void				cleanup_command(t_shell *shell);
void				cleanup_shell(t_shell *shell);
void				free_env(t_shell *shell);
void				*free_env_list(t_env *env);
void				free_env_array(char **env);
void				free_array(char **arr);
char				*ft_strndup(const char *s1, size_t size);
char				*ft_getenv(t_shell *shell, char *name);
size_t				ft_strnlen(const char *str, size_t max_len);
int					ft_isspace(char c);

#endif
