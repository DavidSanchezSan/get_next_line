/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:20 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/20 20:21:36 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes an external command in a child process.
/// @param cmd The command structure containing the external
/// command and its arguments.
/// @param shell The minishell structure containing environment and state.
void	execute_external_in_child(t_command *cmd, t_minishell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
	{
		ft_putstr_fd("minishell:command not found\n", 2);
		exit(127);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		execute_absolute_path(cmd, shell);
	else
		execute_relative_path(cmd, shell);
}

/// @brief Executes command with absolute/relative path
/// @param cmd The command structure
/// @param shell The minishell structure
void	execute_absolute_path(t_command *cmd, t_minishell *shell)
{
	char		**envp;
	struct stat	st;
	int			ret;

	ret = validate_cmd_path(cmd->argv[0], &st);
	if (ret != 0)
		exit(ret);
	envp = convert_env_to_array(shell->env);
	execute_with_path(cmd->argv[0], cmd->argv, envp);
}

/// @brief Executes command from PATH
/// @param cmd The command structure
/// @param shell The minishell structure
void	execute_relative_path(t_command *cmd, t_minishell *shell)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = get_cmd_path(cmd->argv[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	envp = convert_env_to_array(shell->env);
	if (!envp)
		(free(cmd_path), exit(126));
	execve(cmd_path, cmd->argv, envp);
	free(cmd_path);
	free_env(envp);
	exit(127);
}

/// @brief Validates command path and checks permissions
/// @param path The path to validate
/// @param st Pointer to stat structure
/// @return 0 on success, error code on failure
int	validate_cmd_path(char *path, struct stat *st)
{
	if (stat(path, st) != 0)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(path, 2),
			ft_putstr_fd(": No such file or directory\n", 2), 127);
	if (S_ISDIR(st->st_mode))
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(path, 2),
			ft_putstr_fd(": Is a directory\n", 2), 126);
	if (access(path, X_OK) != 0)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(path, 2),
			ft_putstr_fd(": Permission denied\n", 2), 126);
	return (0);
}

/// @brief Executes command with given path
/// @param path The path to execute
/// @param argv Command arguments
/// @param envp Environment variables
void	execute_with_path(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	free_env(envp);
	exit(127);
}
