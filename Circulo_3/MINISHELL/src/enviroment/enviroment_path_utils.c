/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_path_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:09 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:30:10 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if command is absolute or relative path
/// @param cmd The command name
/// @return The duplicated path if valid and executable, NULL otherwise
static char	*check_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

/// @brief Searches for command in PATH directories
/// @param paths Array of PATH directories
/// @param cmd The command name
/// @return Full path if found and executable, NULL otherwise
static char	*search_in_paths(char **paths, char *cmd)
{
	char	*cmd_path;
	char	*new_cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
			return (NULL);
		new_cmd_path = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (!new_cmd_path)
			return (NULL);
		if (access(new_cmd_path, F_OK | X_OK) == 0)
			return (new_cmd_path);
		free(new_cmd_path);
		i++;
	}
	return (NULL);
}

/// @brief Finds the full path of a command by searching PATH directories.
/// @param cmd The command name.
/// @param env The environment variables array.
/// @return The full path to the command if found and executable,
/// otherwise NULL.
char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*result;

	if (!cmd || !env)
		return (NULL);
	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path = get_env_variable(env, "PATH");
	if (!path || path[0] == '\0')
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_split(paths);
	return (result);
}

/// @brief Converts the environment variables linked list to an
/// array of strings.
/// @param env The environment variables linked list.
/// @return An array of strings representing the environment
/// variables, or NULL on failure.
char	**convert_env_to_array(char **env)
{
	int		i;
	char	**envp;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		envp[i] = ft_strdup(env[i]);
		if (!envp[i])
		{
			while (i-- > 0)
				free(envp[i]);
			return (free(envp), NULL);
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
