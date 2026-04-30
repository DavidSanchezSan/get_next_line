/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/16 19:34:32 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes a pipeline of commands.
/// @param head The head of the linked list of commands.
/// @param shell The minishell structure containing environment and state.
/// @return The exit status of the last command in the pipeline.
int	execute_pipeline(t_command *head, t_minishell *shell)
{
	pid_t	*pids;
	int		cmd_count;
	int		status;

	if (!head)
		return (1);
	if (!head->next && !head->pipe_flag)
	{
		status = exec_single_builtin(head, shell);
		if (status != -1)
			return (status);
	}
	cmd_count = count_commands(head);
	pids = (pid_t *)malloc(cmd_count * sizeof(pid_t));
	if (!pids)
		return (perror("malloc"), 1);
	if (process_pipeline(head, shell, pids, cmd_count) != 0)
	{
		if (g_signal == SIGINT)
			return (free(pids), 130);
		return (free(pids), 1);
	}
	status = wait_for_children(pids, cmd_count);
	signals_setup();
	return (free(pids), status);
}

/// @brief Processes all commands in the pipeline
/// @param head The head of the command list
/// @param shell The minishell structure
/// @param pids Array of process IDs
/// @param cmd_count Number of commands
/// @return 0 on success, 1 on failure

int	process_pipeline(t_command *head, t_minishell *shell,
		pid_t *pids, int cmd_count)
{
	t_command	*current;
	t_pipe_ctx	ctx;
	int			pipe_fds[2];
	int			i;

	current = head;
	ctx.pids = pids;
	ctx.prev_fd = -1;
	ctx.pipe_fds = pipe_fds;
	i = 0;
	while (current && i < cmd_count)
	{
		if (process_single_command(current, shell, &ctx, i) != 0)
		{
			if (g_signal == SIGINT)
			{
				kill_created_processes(pids, i);
				return (1);
			}
			return (1);
		}
		current = current->next;
		i++;
	}
	return (0);
}

/// @brief Processes a single command in the pipeline
/// @param cmd The command structure
/// @param shell The minishell structure
/// @param ctx Pipe execution context
/// @param i Current command index
/// @return 0 on success, 1 on failure
int	process_single_command(t_command *cmd, t_minishell *shell,
		t_pipe_ctx *ctx, int i)
{
	if (handle_pipe_creation(cmd, ctx, i) != 0)
		return (1);
	if (open_redirections(cmd, shell->env, shell->ret_val,
			shell->shell_pid) < 0)
		return (handle_redirection_error(cmd, ctx, i));
	signal(SIGINT, SIG_IGN);
	ctx->pids[i] = fork();
	if (ctx->pids[i] == -1)
		return (handle_fork_error(cmd, ctx, i));
	if (ctx->pids[i] == 0)
		execute_child_process(cmd, shell, ctx->prev_fd, ctx->pipe_fds);
	close_parent_fds(cmd, ctx->prev_fd, ctx->pipe_fds);
	if (cmd->pipe_flag)
		ctx->prev_fd = ctx->pipe_fds[0];
	else
		ctx->prev_fd = -1;
	return (0);
}

/// @brief Waits for all child processes to complete
/// @param pids Array of process IDs
/// @param cmd_count Number of commands
/// @return Exit status of last command
int	wait_for_children(pid_t *pids, int cmd_count)
{
	int		exit_status;
	int		status;
	int		i;
	pid_t	wait_result;

	exit_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wait_result = wait_single_child(pids[i], &status);
		if (wait_result != -1)
		{
			status = get_child_exit_status(status, i == cmd_count - 1);
			if (status != -1)
				exit_status = status;
		}
		i++;
	}
	return (exit_status);
}

/// @brief Determines the exit status of a child process.
/// @param status The status value returned by waitpid.
/// @param is_last Indicates if this is the last command in the pipeline.
/// @return The exit status of the child process, or -1 if not applicable.
int	get_child_exit_status(int status, int is_last)
{
	int	sig;

	if (!is_last)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig == SIGTERM)
			ft_putstr_fd("Terminated\n", 2);
		return (128 + sig);
	}
	if (WIFSTOPPED(status))
		return (-1);
	return (-1);
}
