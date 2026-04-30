/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_continuation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:23:56 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/16 00:47:43 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles abortion of continuation on Ctrl+C or EOF
/// @param accumulated The accumulated string to free
/// @param input The current input to free
/// @param shell The shell structure
static void	handle_continuation_abort(char *accumulated, char *input,
	t_minishell *shell)
{
	free(accumulated);
	free(input);
	shell->ret_val = 130;
	g_signal = 0;
}

/// @brief Reads and processes one continuation line
/// @param accumulated Pointer to accumulated string
/// @param tokens Token array pointer
/// @param shell The minishell structure
/// @return process_input return value, or -1 on abort
static int	read_continuation_line(char **accumulated, t_token_array *tokens,
	t_minishell *shell)
{
	char	*input;
	char	*temp;
	char	*result;

	setup_heredoc_signals();
	input = readline("> ");
	if (!input || g_signal == SIGINT)
		return (handle_continuation_abort(*accumulated, input, shell),
			*accumulated = NULL, -1);
	temp = ft_strjoin(*accumulated, " ");
	free(*accumulated);
	*accumulated = NULL;
	if (!temp)
		return (free(input), -1);
	result = ft_strjoin(temp, input);
	free(temp);
	free(input);
	if (!result)
		return (-1);
	*accumulated = result;
	return (process_input(*accumulated, tokens, shell));
}

/// @brief Handles multi-line pipe continuation
/// @param initial The initial input line
/// @param tokens Token array pointer
/// @param shell The minishell structure
/// @return 0 on success, 1 to continue main loop
int	handle_pipe_continuation(char *initial, t_token_array *tokens,
	t_minishell *shell)
{
	char	*accumulated;
	int		ret;

	accumulated = ft_strdup(initial);
	ret = 2;
	while (ret == 2 && accumulated)
		ret = read_continuation_line(&accumulated, tokens, shell);
	free(accumulated);
	if (ret == -1 || ret == 1)
		return (1);
	return (0);
}

/// @brief Handles the result of process_input
/// @param ret Return value from process_input
/// @param input The input string to free
/// @param tokens Token array pointer
/// @param shell The minishell structure
/// @return 0 to continue loop, 1 to break
static int	handle_process_result(int ret, char *input,
	t_token_array *tokens, t_minishell *shell)
{
	if (ret == 2 && handle_pipe_continuation(input, tokens, shell))
	{
		free(input);
		return (0);
	}
	free(input);
	return (0);
}

/// @brief Processes a single iteration of input in the shell loop
/// @param shell The minishell structure
/// @param tokens Token array pointer
/// @return 0 to continue loop, 1 to break loop
int	process_shell_iteration(t_minishell *shell, t_token_array *tokens)
{
	char	*input;
	int		ret;

	input = readline("minishell> ");
	if (g_signal == SIGINT)
	{
		shell->ret_val = 130;
		g_signal = 0;
	}
	if (!input)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	if (!*input)
	{
		free(input);
		return (0);
	}
	ret = process_input(input, tokens, shell);
	return (handle_process_result(ret, input, tokens, shell));
}
