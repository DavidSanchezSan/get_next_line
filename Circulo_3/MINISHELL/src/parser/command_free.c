/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:03:55 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:03:55 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Closes the file descriptors associated with
/// a command if they are open.
/// @param cmd The command structure containing file descriptors.
static void	close_command_fds(t_command *cmd)
{
	if (cmd->infile_fd >= 0)
		close(cmd->infile_fd);
	if (cmd->outfile_fd >= 0)
		close(cmd->outfile_fd);
	if (cmd->heredoc_fd >= 0)
		close(cmd->heredoc_fd);
}

/// @brief Frees the memory allocated for a single command structure,
/// including its arguments and associated files.
/// @param cmd The command structure to free.
void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	close_command_fds(cmd);
	free(cmd);
}

/// @brief Frees the memory allocated for the entire linked list of commands.
/// @param head Pointer to the head of the command list.
void	free_command_list(t_command *head)
{
	t_command	*tmp;

	while (head)
	{
		tmp = head->next;
		free_command(head);
		head = tmp;
	}
}
