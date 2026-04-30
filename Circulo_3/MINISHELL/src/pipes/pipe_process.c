/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/23 18:48:14 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes child process for command
/// @param cmd The command structure
/// @param shell The minishell structure
/// @param prev_fd Previous pipe read fd
/// @param pipe_fds Current pipe fds
void	execute_child_process(t_command *cmd, t_minishell *shell,
		int prev_fd, int pipe_fds[2])
{
	if (cmd == NULL)
		exit(127);
	child_signals_setup();
	setup_child_io(cmd, prev_fd, pipe_fds);
	apply_redirections(cmd);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		execute_builtin_in_child(cmd, shell);
	else
		execute_external_in_child(cmd, shell);
	exit(127);
}

/// @brief Sets up the input and output file descriptors for a child
/// process based on the command's redirections and pipeline status.
/// @param cmd The command structure containing file descriptors for
/// redirections.
/// @param prev_fd The file descriptor for the read end of the previous pipe.
/// @param pipe_fds The file descriptors for the current pipe.
void	setup_child_io(t_command *cmd, int prev_fd, int pipe_fds[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->pipe_flag)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
}

/// @brief Closes file descriptors in the parent process after forking a child.
/// @param cmd The command structure containing file descriptors.
/// @param prev_fd The file descriptor for the read end of the previous pipe.
/// @param pipe_fds The file descriptors for the current pipe.
void	close_parent_fds(t_command *cmd, int prev_fd, int pipe_fds[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->pipe_flag)
		close (pipe_fds[1]);
	if (cmd->infile_fd != -1)
	{
		close (cmd->infile_fd);
		cmd->infile_fd = -1;
	}
	if (cmd->outfile_fd != -1)
	{
		close (cmd->outfile_fd);
		cmd->outfile_fd = -1;
	}
	if (cmd->heredoc_fd != -1)
	{
		close (cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

/// @brief Saves standard file descriptors
/// @param saved_stdin Pointer to store stdin fd
/// @param saved_stdout Pointer to store stdout fd
/// @return 0 on success, 1 on failure
int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (perror("dup"), 1);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		perror("dup");
		return (1);
	}
	return (0);
}

/// @brief Restores standard file descriptors
/// @param saved_stdin The saved stdin fd
/// @param saved_stdout The saved stdout fd
void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
