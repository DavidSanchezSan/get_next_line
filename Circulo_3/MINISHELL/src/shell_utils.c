/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:34:27 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/23 21:05:30 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Initializes and retrieves the shell's process ID by
/// reading /proc/self/stat.
/// @param  void
/// @return The process ID of the shell, or 1 on failure.
int	initialize_shell_pid(void)
{
	int		fd;
	char	buffer[256];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (1);
	if (read(fd, buffer, sizeof(buffer) - 1) <= 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (parse_pid_from_buffer(buffer));
}

/// @brief Parses PID from buffer read from /proc/self/stat
/// @param buffer The buffer containing process info
/// @return The parsed process ID
int	parse_pid_from_buffer(char *buffer)
{
	int	i;
	int	pid;

	buffer[255] = '\0';
	i = 0;
	pid = 0;
	while (buffer[i] && buffer[i] != ' ')
	{
		if (buffer[i] >= '0' && buffer[i] <= '9')
			pid = pid * 10 + (buffer[i] - '0');
		i++;
	}
	return (pid);
}

/// @brief Checks if tokenized command is incomplete (pipe at end)
/// @param tokens The token array
/// @return 1 if incomplete, 0 if complete
static int	is_incomplete_command(t_token_array *tokens)
{
	if (tokens->size == 0)
		return (0);
	if (tokens->tokens[tokens->size - 1].type == TOKEN_PIPE)
		return (1);
	return (0);
}

/// @brief Processes and executes a valid input line
/// @param input The input string
/// @param tokens Pointer to token array
/// @param shell The minishell structure
/// @return 0 on success, 1 if should continue to next iteration 2 if incomplete
int	process_input(char *input, t_token_array *tokens, t_minishell *shell)
{
	if (!tokenize_input(tokens, input, shell))
		return (shell->ret_val = 2, free_tokens(tokens), 1);
	if (tokens->size == 0)
		return (shell->ret_val = 2, free_tokens(tokens), 1);
	if (is_incomplete_command(tokens))
		return (shell->ret_val = 2, free_tokens(tokens), 1);
	add_history(input);
	tokens->shell = shell;
	shell->commands = parse_commands(tokens);
	if (!shell->commands && g_signal == SIGINT)
	{
		shell->ret_val = 130;
		g_signal = 0;
		free_tokens(tokens);
		return (1);
	}
	if (!shell->commands)
		return (shell->ret_val = 2, free_tokens(tokens), 1);
	shell->ret_val = execute_pipeline(shell->commands, shell);
	g_signal = 0;
	signals_setup();
	free_tokens(tokens);
	free_command_list(shell->commands);
	shell->commands = NULL;
	return (0);
}
