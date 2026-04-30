/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:04:29 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:04:29 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Finds the end index of a command in the token array, stopping at a
/// pipe or the end of the array.
/// @param array The array of tokens being parsed.
/// @param i The starting index to search from.
/// @return The index of the pipe token or the end of the array.
int	find_end_command(t_token_array *array, int i)
{
	while (i < array->size && array->tokens[i].type != TOKEN_PIPE)
		i++;
	return (i);
}

/// @brief Links a new command to the linked list of commands.
/// @param head Pointer to the head of the command list.
/// @param current Pointer to the current command in the list.
/// @param new_cmd The new command to link.
void	link_commands(t_command **head, t_command **current,
		t_command *new_cmd)
{
	if (!*head)
		*head = new_cmd;
	else
		(*current)->next = new_cmd;
	*current = new_cmd;
}

/// @brief Checks if the command should be marked as a pipe based on
/// the next token in the array.
/// @param array The array of tokens being parsed.
/// @param new_cmd The command structure to update.
/// @param end The end index of the current command in the token array.
/// @param i Pointer to the current index in the token array.
void	check_pipe(t_token_array *array, t_command *new_cmd, int end, int *i)
{
	if (end < array->size && array->tokens[end].type == TOKEN_PIPE)
	{
		new_cmd->pipe_flag = 1;
		*i = end + 1;
	}
	else
		*i = end;
}
