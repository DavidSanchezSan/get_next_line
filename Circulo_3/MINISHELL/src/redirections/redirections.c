/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:23:36 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/21 10:59:49 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Closes all opened redirection file descriptors
/// @param cmd The command structure containing file descriptors
static void	close_redirect_fds(t_command *cmd)
{
	if (cmd->infile_fd >= 0)
		close(cmd->infile_fd);
	if (cmd->outfile_fd >= 0)
		close(cmd->outfile_fd);
	if (cmd->heredoc_fd >= 0)
		close(cmd->heredoc_fd);
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->heredoc_fd = -1;
}

int	open_redirections(t_command *cmd, char **env, int last_status,
		int shell_pid)
{
	(void)env;
	(void)last_status;
	(void)shell_pid;
	if (cmd->infile_fd != -1 || cmd->outfile_fd != -1)
		return (ft_putstr_fd("Error: FD's not initialized to -1\n", 2), -1);
	if (cmd->infile)
	{
		cmd->infile_fd = open_infile(cmd);
		if (cmd->infile_fd < 0)
			return (-1);
	}
	if (cmd->outfile)
	{
		cmd->outfile_fd = open_outfile(cmd);
		if (cmd->outfile_fd < 0)
			return (close_redirect_fds(cmd), -1);
	}
	return (0);
}

/// @brief Applies input redirection (infile or heredoc)
/// @param cmd The command structure
static void	apply_input_redirection(t_command *cmd)
{
	if (cmd->infile_fd != -1)
	{
		if (dup2(cmd->infile_fd, STDIN_FILENO) == -1)
			(perror("Error in dup2 for infile"), exit(1));
		close(cmd->infile_fd);
	}
	else if (cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
			(perror("Error in dup2 for heredoc"), exit(1));
		close(cmd->heredoc_fd);
	}
}

/// @brief Applies the input and output redirections for the given command.
/// @param cmd The command structure containing fd's for redirections.
void	apply_redirections(t_command *cmd)
{
	if (cmd == NULL)
		return ;
	apply_input_redirection(cmd);
	if (cmd->outfile_fd != -1)
	{
		if (dup2(cmd->outfile_fd, STDOUT_FILENO) == -1)
			(perror("Error in dup2 for outfile"), exit(1));
		close(cmd->outfile_fd);
	}
}
