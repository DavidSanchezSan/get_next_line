/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:06:41 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/10 01:13:02 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles word token by duplicating it to argv
/// @param cmd Command structure
/// @param token_value Token value to duplicate
/// @param argc Pointer to argument counter
/// @return 0 on success, -1 on error
int	handle_word_token(t_command *cmd, char *token_value, int *argc)
{
	cmd->argv[*argc] = ft_strdup(token_value);
	if (cmd->argv[*argc] == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		free_command(cmd);
		return (-1);
	}
	(*argc)++;
	return (0);
}

/// @brief Processes a single token based on its type
/// @param cmd Command structure
/// @param array Token array
/// @param range Token range with index and end
/// @param argc Pointer to argument counter
/// @return 0 on success, -1 on error
int	process_command_token(t_command *cmd, t_token_array *array,
		t_token_range *range, int *argc)
{
	t_token	token;

	token = array->tokens[*range->i];
	if (token.type == TOKEN_REDIRECT_IN)
		return (handle_redirect_in(cmd, array, range->i, range->end));
	else if (token.type == TOKEN_REDIRECT_OUT)
		return (handle_redirect_out(cmd, array, range->i, range->end));
	else if (token.type == TOKEN_APPEND)
		return (handle_append(cmd, array, range->i, range->end));
	else if (token.type == TOKEN_HERE_DOC)
		return (handle_heredoc(cmd, array, range->i, range->end));
	else if (token.type == TOKEN_WORD)
		return (handle_word_token(cmd, token.value, argc));
	return (0);
}

/// @brief Validates that command has at least one argument or redirection
/// @param cmd Command structure
/// @param argc Number of arguments
/// @return 0 if valid, -1 if invalid
int	validate_command(t_command *cmd, int argc)
{
	if (argc == 0 && !cmd->infile && !cmd->outfile && !cmd->heredoc)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		free_command(cmd);
		return (-1);
	}
	return (0);
}

/// @brief Validates pipe syntax at the beginning of input
/// @param array The array of tokens being parsed
/// @return 0 if valid, -1 if invalid
int	validate_pipe_syntax(t_token_array *array)
{
	if (array->size > 0 && array->tokens[0].type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	return (0);
}
