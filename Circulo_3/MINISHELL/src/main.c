/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:34:27 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/16 00:06:29 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Cleans up and removes temporary heredoc files from the /tmp directory
static void	cleanup_heredoc_files(void)
{
	DIR				*dir;
	char			*full_path;
	struct dirent	*entry;

	dir = opendir("/tmp");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".heredoc_", 9) == 0)
		{
			full_path = ft_strjoin("/tmp/", entry->d_name);
			if (full_path && (unlink(full_path), 1))
				free(full_path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

/// @brief Cleans up and frees allocated memory and resources used by the shell.
/// @param shell The minishell structure containing environment and state.
static void	clean_memory(t_minishell *shell)
{
	free_env(shell->env);
	clear_history();
	rl_clear_history();
	cleanup_heredoc_files();
}

/// @brief Initializes and retrieves the shell's process ID.
/// @param shell The minishell structure containing environment and state.
/// @param envp The environment variables passed to the shell.
static void	init_shell(t_minishell *shell, char **envp)
{
	int	env_count;

	shell->env = ft_dup_env(envp);
	if (!shell->env)
		return ;
	env_count = 0;
	while (shell->env[env_count])
		env_count++;
	shell->env_capacity = env_count + 11;
	shell->commands = NULL;
	shell->ret_val = 0;
	shell->shell_pid = initialize_shell_pid();
	signals_setup();
}

/// @brief Main loop for the shell
/// @param shell The minishell structure
static void	shell_loop(t_minishell *shell)
{
	t_token_array	tokens;

	while (1)
	{
		g_signal = 0;
		if (process_shell_iteration(shell, &tokens))
			break ;
	}
}

/// @brief The main entry point of the minishell program.
/// @param argc The number of command-line arguments.
/// @param argv The array of command-line arguments.
/// @param envp The array of environment variables.
/// @return The exit status of the shell.
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	shell_loop(&shell);
	clean_memory(&shell);
	return (shell.ret_val);
}
