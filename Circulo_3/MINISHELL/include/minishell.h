/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:01:41 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:01:41 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/// Definition of constants
# define MAX_EXPANSION_SIZE 262144

/// @brief Global variable to handle signals
extern volatile sig_atomic_t	g_signal;

/// @brief Structure to represent a command
typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					heredoc;
	char				*heredoc_delimiter;
	int					heredoc_quoted;
	int					append;
	int					pipe_flag;
	int					infile_fd;
	int					outfile_fd;
	int					heredoc_fd;
	struct s_command	*next;
}	t_command;

/// @brief Enumeration to classify token types
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HERE_DOC,
	TOKEN_ERROR
}	t_token_type;

/// @brief Enumeration to classify quote types
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
}	t_quote_type;

/// @brief Structure to represent a token, with its value, type, and quote type
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
}	t_token;

/// @brief Structure to represent the full state of the shell
typedef struct s_minishell
{
	char		**env;
	int			env_capacity;
	t_command	*commands;
	int			ret_val;
	int			shell_pid;
}	t_minishell;

/// @brief Structure to manage a dynamic array of tokens, with size and capacity
typedef struct s_token_array
{
	t_token		*tokens;
	int			size;
	int			capacity;
	t_minishell	*shell;
}	t_token_array;

/// @brief Structure for expansion context
typedef struct s_exp_ctx
{
	char		*res;
	size_t		j;
	size_t		cap;
	char		**env;
}	t_exp_ctx;

/// @brief Structure for heredoc context
typedef struct s_heredoc_ctx
{
	char		**env;
	int			last_status;
	int			shell_pid;
}	t_heredoc_ctx;

/// @brief Structure for pipe execution context
typedef struct s_pipe_ctx
{
	pid_t		*pids;
	int			count;
	int			prev_fd;
	int			*pipe_fds;
}	t_pipe_ctx;

/// @brief Structure for token parsing range
typedef struct s_token_range
{
	int			*i;
	int			end;
}	t_token_range;

// Tokenizer utils:
int				is_space(char c);
int				is_operator(char c);
int				is_quote(char c);
void			free_tokens(t_token_array *array);
t_token_type	classify_token_type(char *value);

// Tokenizer init:
int				tokenize_input(t_token_array *array, char *input,
					t_minishell *shell);

// Tokenizer advance:
int				advance_index(char *input, int i, t_token_array *array);
int				process_unquoted_section(char *token_value, int *i,
					char **result, t_minishell *shell);
// Tokenizer add utils:
int				process_quoted_part(char *token_value, int *i, char **result,
					t_minishell *shell);
// Tokenizer add:
int				extract_and_add_token(t_token_array *array,
					char *token_value, t_minishell *shell);
int				append_part(char **result, char *part, int expand,
					t_minishell *shell);

// Parser:
t_command		*parse_commands(t_token_array *array);
int				validate_pipe_syntax(t_token_array *array);

t_command		*build_command_from_tokens(t_token_array *array, int start,
					int end);

//Command_free:
void			free_command(t_command *csmd);
void			free_command_list(t_command *head);
// Command utils:
int				find_end_command(t_token_array *array, int i);
void			link_commands(t_command **head, t_command **current,
					t_command *new_cmd);
void			check_pipe(t_token_array *array, t_command *new_cmd,
					int end, int *i);

// Parser helpers:
int				handle_word_token(t_command *cmd, char *token_value, int *argc);
int				process_command_token(t_command *cmd, t_token_array *array,
					t_token_range *range, int *argc);
int				validate_command(t_command *cmd, int argc);
int				validate_pipe_syntax(t_token_array *array);

//command_init
t_command		*init_command(t_token_array *array, int start,
					int end);
// Redirect_handlers:
int				handle_redirect_in(t_command *cmd, t_token_array *array,
					int *i, int end);
int				handle_redirect_out(t_command *cmd, t_token_array *array,
					int *i, int end);
int				handle_append(t_command *cmd, t_token_array *array,
					int *i, int end);
int				handle_heredoc(t_command *cmd, t_token_array *array,
					int *i, int end);

// Redirect file operations:
int				open_and_truncate_file(const char *filename);
int				open_append_file(const char *filename);

// Heredoc redirections:
int				open_heredoc(t_command *cmd, char **env, int last_status,
					int shell_pid);
int				process_heredoc_now(t_command *cmd, t_minishell *shell);

// Redirections utils:
int				open_outfile(t_command *cmd);
int				open_infile(t_command *cmd);
int				create_heredoc_template(int shell_pid, char *template);
char			*process_heredoc_line(char *line, t_command *cmd,
					t_heredoc_ctx *hd_ctx);
int				is_heredoc_delimiter(char *line, char *delimiter);

// Redirections:
int				open_redirections(t_command *cmd, char **env, int last_status,
					int shell_pid);
void			apply_redirections(t_command *cmd);

// Built - in functions:
char			*search_home(char **env);
int				name_var_check(char *s);
void			sort_env_array(char **sorted, int count);
void			print_export_var(char *var);
void			ft_export_print(char **env);
int				ft_cd(char **argv, char ***env, int *env_capacity);
int				ft_upd_env(char ***env, int *env_cap, const char *key,
					const char *value);
int				ft_echo(char **args);
int				ft_env(char **env, int argc, char **argv);
int				ft_exit(char **args, int current_status);
int				ft_export(char **args, char ***env, int *env_capacity);
int				add_var(char ***env, char *new_var, int *env_capacity);
int				ft_pwd(void);
int				ft_unset(char *var, char **env);

// Environment path utils:
char			*get_cmd_path(char *cmd, char **env);
char			**convert_env_to_array(char **env);

// Environment variables utils:
char			*get_variable_value(char **env, char *var_name);
char			**ft_dup_env(char **envp);
void			free_env(char **env);
void			free_split(char **split);
char			*get_env_variable(char **env, char *key);

// Environment variables:
char			*exp_tok_val(char *value, char **env, int last_status,
					int shell_pid);
char			*expand_heredoc_content(char *value,
					t_heredoc_ctx *hd_ctx);

// Expansion helpers:
char			*grow_buffer(char *old, int used, size_t *capacity);
char			*append_char(char *res, size_t *j, size_t *cap, char c);
char			*append_string(char *res, size_t *j, size_t *cap, char *str);
char			*expand_double_dollar(char *res, size_t *j, size_t *cap,
					int shell_pid);
char			*extract_var_value(char *value, int *i, char **env);
// Expansion process:
char			*exp_quest_mark(char *res, size_t *j, size_t *cap,
					int last_status);
char			*process_dollar_token(char *value, int *i, t_exp_ctx *ctx,
					t_minishell *shell);
char			*process_dollar_heredoc(char *value, int *i,
					t_exp_ctx *ctx, t_heredoc_ctx *hd_ctx);
char			*init_expansion_buffer(char *value, size_t *cap);

// Signals:
void			signals_setup(void);
void			sigint_handler(int signal);
void			child_signals_setup(void);
void			setup_heredoc_signals(void);
void			sigint_handler_heredoc(int sig);
void			cleanup_handler(int sig);

// Pipe_builtin:
void			execute_builtin_in_child(t_command *cmd, t_minishell *shell);
void			execute_unset_in_child(t_command *cmd, char **env);
int				run_builtin_cmd(t_command *cmd, t_minishell *shell);
int				execute_unset_builtin(t_command *cmd, char **env);
int				exec_single_builtin(t_command *cmd, t_minishell *shell);
// Pipe_executor:
int				execute_pipeline(t_command *head, t_minishell *shell);
int				process_pipeline(t_command *head, t_minishell *shell,
					pid_t *pids, int cmd_count);
int				process_single_command(t_command *cmd, t_minishell *shell,
					t_pipe_ctx *ctx, int i);
int				wait_for_children(pid_t *pids, int cmd_count);
int				get_child_exit_status(int status, int is_last);
// Pipe_external:
void			execute_external_in_child(t_command *cmd, t_minishell *shell);
void			execute_absolute_path(t_command *cmd, t_minishell *shell);
void			execute_relative_path(t_command *cmd, t_minishell *shell);
int				validate_cmd_path(char *path, struct stat *st);
void			execute_with_path(char *path, char **argv, char **envp);
// Pipe_helpers:
int				is_builtin(char *cmd);
int				count_commands(t_command *head);
pid_t			wait_single_child(pid_t pid, int *status);
int				handle_env_exit(t_command *cmd, t_minishell *shell);
void			kill_created_processes(pid_t *pids, int count);
// Pipe_process:
void			execute_child_process(t_command *cmd, t_minishell *shell,
					int prev_fd, int pipe_fds[2]);
void			setup_child_io(t_command *cmd, int prev_fd, int pipe_fds[2]);
void			close_parent_fds(t_command *cmd, int prev_fd, int pipe_fds[2]);
int				save_std_fds(int *saved_stdin, int *saved_stdout);
void			restore_std_fds(int saved_stdin, int saved_stdout);
// Pipe_utils:
void			cleanup_fds_and_wait(t_pipe_ctx *ctx, int has_pipe,
					int num_processes);
int				handle_pipe_creation(t_command *cmd, t_pipe_ctx *ctx, int i);
int				handle_redirection_error(t_command *cmd,
					t_pipe_ctx *ctx, int i);
int				handle_fork_error(t_command *cmd, t_pipe_ctx *ctx, int i);
int				handle_exit_builtin(t_command *cmd, t_minishell *shell,
					int saved_stdin, int saved_stdout);
// Shell_utils:
int				initialize_shell_pid(void);
int				parse_pid_from_buffer(char *buffer);
int				handle_input_interrupt(t_minishell *shell);
int				process_input(char *input, t_token_array *tokens,
					t_minishell *shell);

// Shell_continuation:
int				handle_pipe_continuation(char *initial, t_token_array *tokens,
					t_minishell *shell);
int				process_shell_iteration(t_minishell *shell,
					t_token_array *tokens);

#endif
