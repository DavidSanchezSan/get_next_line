/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:06:41 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:06:41 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Processes a single command segment from tokens
/// @param array The array of tokens being parsed
/// @param i Pointer to current index in the token array
/// @param head Pointer to the head of the command list
/// @param current Pointer to the current command in the list
/// @return 1 on success, 0 on error
static int	process_next_command(t_token_array *array, int *i,
	t_command **head, t_command **current)
{
	int			start;
	int			end;
	t_command	*new_cmd;

	start = *i;
	end = find_end_command(array, *i);
	new_cmd = build_command_from_tokens(array, start, end);
	if (!new_cmd)
		return (0);
	check_pipe(array, new_cmd, end, i);
	link_commands(head, current, new_cmd);
	return (1);
}

/// @brief Finalizes command structure with validation
/// @param cmd The command structure
/// @param argc The argument count
/// @return 0 on success, -1 on error
static int	finalize_command(t_command *cmd, int argc)
{
	if (validate_command(cmd, argc) < 0)
		return (-1);
	cmd->argv[argc] = NULL;
	return (0);
}

/// @brief Parses the array of tokens into a linked list of command
/// structures, handling pipes and redirections.
/// @param array The array of tokens being parsed.
/// @return A pointer to the head of the linked list of commands,
/// or NULL on error.
t_command	*parse_commands(t_token_array *array)
{
	int			i;
	t_command	*head;
	t_command	*current;

	if (validate_pipe_syntax(array) == -1)
		return (NULL);
	head = NULL;
	current = NULL;
	i = 0;
	while (i < array->size)
	{
		if (!process_next_command(array, &i, &head, &current))
		{
			free_command_list(head);
			return (NULL);
		}
	}
	return (head);
}

/// @brief Handles signal error for command processing
/// @param array The token array with shell context
static void	handle_signal_error(t_token_array *array)
{
	if (g_signal == SIGINT)
	{
		if (array->shell)
			array->shell->ret_val = 130;
	}
}

/// @brief Builds a structure of commands from tokens.
/// @param array The array of tokens being parsed.
/// @param start The start index of the token range.
/// @param end The end index of the token range.
/// @return A pointer to the constructed command structure, or NULL on error.
t_command	*build_command_from_tokens(t_token_array *array, int start, int end)
{
	int				i;
	int				argc;
	t_command		*cmd;
	t_token_range	range;

	argc = 0;
	cmd = init_command(array, start, end);
	if (!cmd)
		return (NULL);
	i = start;
	range.i = &i;
	range.end = end;
	while (i < end)
	{
		if (process_command_token(cmd, array, &range, &argc) < 0)
		{
			handle_signal_error(array);
			return (NULL);
		}
		i++;
	}
	if (finalize_command(cmd, argc) < 0)
		return (NULL);
	return (cmd);
}
