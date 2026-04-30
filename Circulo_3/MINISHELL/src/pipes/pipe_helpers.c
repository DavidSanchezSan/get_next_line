/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/16 19:34:09 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if the given command is a built-in shell command.
/// @param cmd The command string to check.
/// @return 1 if the command is a built-in, 0 otherwise.
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

/// @brief Counts the number of commands in the linked list.
/// @param head The head of the linked list of commands.
/// @return The number of commands in the list.
int	count_commands(t_command *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

/// @brief Waits for a single child process, handling interrupts and stops
/// @param pid The process ID to wait for
/// @param status Pointer to store the status
/// @return The result from waitpid
pid_t	wait_single_child(pid_t pid, int *status)
{
	pid_t	wait_result;

	wait_result = waitpid(pid, status, 0);
	signal(SIGINT, sigint_handler);
	while (wait_result == -1 && errno == EINTR)
		wait_result = waitpid(pid, status, 0);
	while (wait_result != -1 && WIFSTOPPED(*status))
	{
		wait_result = waitpid(pid, status, 0);
		while (wait_result == -1 && errno == EINTR)
			wait_result = waitpid(pid, status, 0);
	}
	return (wait_result);
}

/// @brief Handles env and exit builtins in child process
/// @param cmd The command structure
/// @param shell The minishell structure
/// @return 1 if handled, 0 if not handled
int	handle_env_exit(t_command *cmd, t_minishell *shell)
{
	int	status;
	int	argc;

	if (!ft_strncmp(cmd->argv[0], "env", 4))
	{
		argc = 0;
		while (cmd->argv[argc])
			argc++;
		exit(ft_env(shell->env, argc, cmd->argv));
	}
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
	{
		status = ft_exit(cmd->argv, shell->ret_val);
		if (status == -1)
			exit(1);
		else
			exit(status);
	}
	return (0);
}

/// @brief Terminates all previously created child processes
/// @param pids Array of process IDs to terminate
/// @param count Number of processes in the array
void	kill_created_processes(pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
			kill(pids[i], SIGTERM);
		i++;
	}
}
