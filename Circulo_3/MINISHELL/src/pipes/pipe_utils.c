/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/17 18:59:58 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Cleans up file descriptors without freeing pids
/// @param ctx Pipe execution context
/// @param has_pipe Whether current command has pipe
/// @param num_processes Number of processes to wait for
void	cleanup_fds_and_wait(t_pipe_ctx *ctx, int has_pipe, int num_processes)
{
	int	j;

	if (ctx->prev_fd != -1)
		close(ctx->prev_fd);
	if (has_pipe && ctx->pipe_fds)
	{
		close(ctx->pipe_fds[0]);
		close(ctx->pipe_fds[1]);
	}
	j = 0;
	while (j < num_processes)
		waitpid(ctx->pids[j++], NULL, 0);
}

/// @brief Creates pipe for command if needed
/// @param cmd The command structure
/// @param ctx Pipe execution context
/// @param i Current command index
/// @return 0 on success, 1 on failure
int	handle_pipe_creation(t_command *cmd, t_pipe_ctx *ctx, int i)
{
	ctx->count = i;
	if (cmd->pipe_flag && pipe(ctx->pipe_fds) == -1)
	{
		perror("pipe");
		cleanup_fds_and_wait(ctx, 0, i);
		free(ctx->pids);
		return (1);
	}
	return (0);
}

/// @brief Handles redirection error in pipeline
/// @param cmd The command structure
/// @param ctx Pipe execution context
/// @param i Current command index
/// @return 1 (always fails)
int	handle_redirection_error(t_command *cmd, t_pipe_ctx *ctx, int i)
{
	int	j;

	if (g_signal == SIGINT)
	{
		if (ctx->prev_fd != -1)
			close(ctx->prev_fd);
		if (cmd->pipe_flag)
		{
			close(ctx->pipe_fds[0]);
			close(ctx->pipe_fds[1]);
		}
		if (i > 0)
		{
			j = 0;
			while (j < i)
				waitpid(ctx->pids[j++], NULL, 0);
		}
		return (1);
	}
	ctx->count = i;
	cleanup_fds_and_wait(ctx, cmd->pipe_flag, i);
	return (1);
}

/// @brief Handles fork error in pipeline
/// @brief Handles fork error in pipeline
/// @param cmd The command structure
/// @param ctx Pipe execution context
/// @param i Current command index
/// @return 1 (always fails)
int	handle_fork_error(t_command *cmd, t_pipe_ctx *ctx, int i)
{
	perror("fork");
	ctx->count = i;
	cleanup_fds_and_wait(ctx, cmd->pipe_flag, i);
	free(ctx->pids);
	return (1);
}

/// @brief Handles exit builtin in single command context
/// @param cmd The command structure
/// @param shell The minishell structure
/// @param saved_stdin The saved stdin fd
/// @param saved_stdout The saved stdout fd
/// @return Exit status
int	handle_exit_builtin(t_command *cmd, t_minishell *shell,
		int saved_stdin, int saved_stdout)
{
	int	ret;

	ft_putstr_fd("exit\n", 2);
	ret = ft_exit(cmd->argv, shell->ret_val);
	restore_std_fds(saved_stdin, saved_stdout);
	if (ret == -1)
		return (1);
	free_env(shell->env);
	exit(ret);
}
