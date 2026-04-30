/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:06:52 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:06:52 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles the parsing of an input redirection (<).
/// @param cmd The command structure to update.
/// @param array The array of tokens being parsed.
/// @param i Pointer to the current index in the token array.
/// @param end The end index of the token array.
/// @return 0 on success, -1 on error.
int	handle_redirect_in(t_command *cmd, t_token_array *array, int *i, int end)
{
	if (*i + 1 >= end || array->tokens[*i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '<'\n", 2);
		free_command(cmd);
		return (-1);
	}
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->heredoc_delimiter != NULL)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
		cmd->heredoc = 0;
		cmd->heredoc_quoted = 0;
	}
	cmd->infile = ft_strdup(array->tokens[++(*i)].value);
	if (cmd->infile == NULL)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		free_command(cmd);
		return (-1);
	}
	return (0);
}

/// @brief Handles the parsing of an output redirection (>).
/// @param cmd The command structure to update.
/// @param array The array of tokens being parsed.
/// @param i Pointer to the current index in the token array.
/// @param end The end index of the token array.
/// @return 0 on success, -1 on error.
int	handle_redirect_out(t_command *cmd, t_token_array *array, int *i, int end)
{
	if (*i + 1 >= end || array->tokens[*i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '>'\n", 2);
		free_command(cmd);
		return (-1);
	}
	if (cmd->outfile != NULL)
	{
		if (open_and_truncate_file(cmd->outfile) == -1)
		{
			free_command(cmd);
			return (-1);
		}
		free(cmd->outfile);
	}
	cmd->outfile = ft_strdup(array->tokens[++(*i)].value);
	if (cmd->outfile == NULL)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		free_command(cmd);
		return (-1);
	}
	cmd->append = 0;
	return (0);
}

/// @brief Handles the parsing of an append redirection (>>).
/// @param cmd The command structure to update.
/// @param array The array of tokens being parsed.
/// @param i Pointer to the current index in the token array.
/// @param end The end index of the token array.
/// @return 0 on success, -1 on error.
int	handle_append(t_command *cmd, t_token_array *array, int *i, int end)
{
	if (*i + 1 >= end || array->tokens[*i + 1].type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n", 2);
		free_command(cmd);
		return (-1);
	}
	if (cmd->outfile != NULL)
	{
		if (open_append_file(cmd->outfile) == -1)
		{
			free_command(cmd);
			return (-1);
		}
		free(cmd->outfile);
	}
	cmd->outfile = ft_strdup(array->tokens[++(*i)].value);
	if (cmd->outfile == NULL)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		free_command(cmd);
		return (-1);
	}
	cmd->append = 1;
	return (0);
}

/// @brief Validates heredoc token and checks for errors
/// @param cmd The command structure
/// @param array The array of tokens being parsed
/// @param i Current index in the token array
/// @brief Validates and prepares heredoc delimiter
/// @param cmd The command structure
/// @param array The array of tokens being parsed
/// @param i Current index in the token array
/// @param end The end index of the token array
/// @return 0 on success, -1 on error
static int	prepare_heredoc(t_command *cmd, t_token_array *array,
	int i, int end)
{
	if (i + 1 >= end || array->tokens[i + 1].type != TOKEN_WORD)
		return (ft_putstr_fd("minishell: syntax error near "
				"unexpected token '<<'\n", 2), free_command(cmd), -1);
	if (array->tokens[i + 1].value == NULL
		|| ft_strlen(array->tokens[i + 1].value) == 0)
		return (ft_putstr_fd("minishell: heredoc delimiter "
				"cannot be empty\n", 2), free_command(cmd), -1);
	if (cmd->heredoc_delimiter != NULL)
		free(cmd->heredoc_delimiter);
	if (cmd->infile != NULL)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	cmd->heredoc_delimiter = ft_strdup(array->tokens[i + 1].value);
	if (!cmd->heredoc_delimiter)
		return (-1);
	if (array->tokens[i + 1].quote != QUOTE_NONE)
		cmd->heredoc_quoted = 1;
	else
		cmd->heredoc_quoted = 0;
	return (0);
}

/// @brief Handles the parsing of a heredoc redirection (<<).
/// @param cmd The command structure to update.
/// @param array The array of tokens being parsed.
/// @param i Pointer to the current index in the token array.
/// @param end The end index of the token array.
/// @return 0 on success, -1 on error.
int	handle_heredoc(t_command *cmd, t_token_array *array, int *i, int end)
{
	int	new_fd;

	if (prepare_heredoc(cmd, array, *i, end) == -1)
		return (-1);
	if (cmd->heredoc_fd >= 0)
		close(cmd->heredoc_fd);
	new_fd = process_heredoc_now(cmd, array->shell);
	if (new_fd < 0)
		return (free_command(cmd), -1);
	cmd->heredoc_fd = new_fd;
	cmd->heredoc = 1;
	(*i)++;
	return (0);
}
