/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/04 18:29:30 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes a built-in command in a child process.
/// @param cmd The command structure containing the built-in command
/// and its arguments.
/// @param shell The minishell structure containing environment and state.
void	execute_builtin_in_child(t_command *cmd, t_minishell *shell)
{
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		exit(ft_cd(cmd->argv, &shell->env, &shell->env_capacity));
	else if (!ft_strncmp(cmd->argv[0], "echo", 5))
		exit(ft_echo(cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		exit(ft_pwd());
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		exit(ft_export(cmd->argv, &shell->env, &shell->env_capacity));
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		execute_unset_in_child(cmd, shell->env);
	else if (handle_env_exit(cmd, shell))
		return ;
	else
		exit(127);
}

/// @brief Executes unset command in child process
/// @param cmd The command structure
/// @param env The environment variables
void	execute_unset_in_child(t_command *cmd, char **env)
{
	int	j;

	j = 1;
	while (cmd->argv[j])
	{
		ft_unset(cmd->argv[j], env);
		j++;
	}
	exit(0);
}

/// @brief Executes a built-in command. If the command is "exit",
// it will exit the shell with the appropriate status.
/// @param cmd The command structure containing the built-in command and
/// its arguments.
/// @param shell The minishell structure containing environment and state.
/// @return The exit status of the built-in command.
int	run_builtin_cmd(t_command *cmd, t_minishell *shell)
{
	int	argc;

	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (ft_echo(cmd->argv));
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (ft_cd(cmd->argv, &shell->env, &shell->env_capacity));
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (ft_export(cmd->argv, &shell->env, &shell->env_capacity));
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (execute_unset_builtin(cmd, shell->env));
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
	{
		argc = 0;
		while (cmd->argv[argc])
			argc++;
		return (ft_env(shell->env, argc, cmd->argv));
	}
	return (0);
}

/// @brief Executes unset builtin in parent process
/// @param cmd The command structure
/// @param env The environment variables
/// @return 0 on success
int	execute_unset_builtin(t_command *cmd, char **env)
{
	int	j;

	j = 1;
	while (cmd->argv[j])
	{
		ft_unset(cmd->argv[j], env);
		j++;
	}
	return (0);
}

/// @brief Executes a single built-in command without forking a new process.
/// @param cmd The command structure containing the built-in command and
/// its arguments.
/// @param shell The minishell structure containing environment and state.
/// @return The exit status of the built-in command.
int	exec_single_builtin(t_command *cmd, t_minishell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	if (!cmd->argv[0] || !is_builtin(cmd->argv[0]))
		return (-1);
	if (open_redirections(cmd, shell->env, shell->ret_val,
			shell->shell_pid) < 0)
		return (1);
	if (save_std_fds(&saved_stdin, &saved_stdout) != 0)
		return (1);
	apply_redirections(cmd);
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (handle_exit_builtin(cmd, shell, saved_stdin, saved_stdout));
	ret = run_builtin_cmd(cmd, shell);
	restore_std_fds(saved_stdin, saved_stdout);
	return (ret);
}
