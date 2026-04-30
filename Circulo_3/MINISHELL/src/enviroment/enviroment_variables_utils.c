/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variables_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:29:09 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:30:10 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Retrieves the value of an environment variable.
/// @param env The environment variables array.
/// @param var_name The name of the environment variable.
/// @return The value of the environment variable, or NULL if not found.
char	*get_variable_value(char **env, char *var_name)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(&env[i][ft_strlen(var_name) + 1]));
		i++;
	}
	return (NULL);
}

/// @brief Duplicates the environment variables array.
/// @param envp The environment variables array to duplicate.
/// @return A newly allocated copy of the environment variables array,
/// or NULL on failure.
char	**ft_dup_env(char **envp)
{
	int		i;
	int		count;
	char	**dup;

	i = 0;
	count = 0;
	while (envp[i])
		i++;
	count = i;
	dup = malloc((count + 11) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			return (free(dup), NULL);
		}
		i++;
	}
	return (dup[i] = NULL, dup);
}

/// @brief Frees a NULL-terminated array of environment variable strings.
/// @param env The environment variables array to free.
void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

/// @brief Frees a NULL-terminated array of strings.
/// @param split The array of strings to free.
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/// @brief Retrieves the value of an environment variable by its key.
/// @param env The environment variables array.
/// @param key The key of the environment variable to retrieve.
/// @return The value of the environment variable, or NULL if not found.
char	*get_env_variable(char **env, char *key)
{
	int		i;
	size_t	key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
