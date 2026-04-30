/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:12 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:04:12 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Counts the number of tokens of type WORD in a given range.
/// @param array The array of tokens being parsed.
/// @param start The start index of the token range.
/// @param end The end index of the token range.
/// @return The count of WORD tokens in the specified range.
static int	count_word_tokens(t_token_array *array, int start, int end)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (i < end)
	{
		if (array->tokens[i].type == TOKEN_WORD)
			count++;
		i++;
	}
	return (count);
}

/// @brief Initializes all fields of a command structure to default values
/// @param cmd The command structure to initialize
/// @param word_count The number of word tokens for argv allocation
static void	init_command_fields(t_command *cmd, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count + 1)
	{
		cmd->argv[i] = NULL;
		i++;
	}
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->heredoc_quoted = 0;
	cmd->pipe_flag = 0;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
}

/// @brief Initializes a new command structure with allocated
/// memory for arguments.
/// @param array The array of tokens being parsed.
/// @param start The start index of the token range.
/// @param end The end index of the token range.
/// @return A pointer to the initialized command structure, or NULL on error.
t_command	*init_command(t_token_array *array, int start, int end)
{
	t_command	*cmd;
	int			word_count;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	word_count = count_word_tokens(array, start, end);
	cmd->argv = malloc((word_count + 1) * sizeof(char *));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	init_command_fields(cmd, word_count);
	return (cmd);
}
