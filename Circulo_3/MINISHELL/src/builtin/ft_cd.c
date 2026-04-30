/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:01:13 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:01:13 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Creates a "key=value" string for environment variable
/// @param key The key of the environment variable
/// @param value The value to set for the environment variable
/// @return The allocated string, or NULL on failure
static char	*create_env_string(const char *key, const char *value)
{
	char	*new_var;
	size_t	key_len;
	size_t	new_var_size;

	key_len = ft_strlen(key);
	new_var_size = key_len + ft_strlen(value) + 2;
	new_var = malloc(new_var_size);
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, key, new_var_size);
	ft_strlcat(new_var, "=", new_var_size);
	ft_strlcat(new_var, value, new_var_size);
	return (new_var);
}

/// @brief Tries to update an existing environment variable
/// @param env The environment array
/// @param key The key to search for
/// @param new_var The new string to replace with
/// @return 1 if variable was found and updated, 0 otherwise
static int	try_update_existing(char **env, const char *key, char *new_var)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

/// @brief Expands capacity if needed and adds new variable
/// @param env The environment array pointer
/// @param env_cap The capacity pointer
/// @param i The index to add the variable at
/// @param new_var The variable string to add
/// @return 0 on success, 1 on failure
static int	add_new_env_var(char ***env, int *env_cap, int i, char *new_var)
{
	char	**new_env;

	if (i + 1 >= *env_cap)
	{
		new_env = malloc(sizeof(char *) * (*env_cap + 16));
		if (!new_env)
			return (1);
		ft_memcpy(new_env, *env, sizeof(char *) * i);
		free(*env);
		*env = new_env;
		*env_cap = *env_cap + 16;
	}
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
	return (0);
}

/// @brief Updates or adds an environment variable in the environment array.
/// @param env The environment array.
/// @param env_cap The capacity of the environment array.
/// @param key The key of the environment variable to update or add.
/// @param value The value to set for the environment variable.
/// @return Returns 0 on success, 1 on failure.
int	ft_upd_env(char ***env, int *env_cap, const char *key, const char *value)
{
	char	*new_var;
	int		i;

	if (!key || !env || !*env || !env_cap || !value)
		return (1);
	new_var = create_env_string(key, value);
	if (!new_var)
		return (1);
	if (try_update_existing(*env, key, new_var))
		return (0);
	i = 0;
	while ((*env)[i])
		i++;
	if (add_new_env_var(env, env_cap, i, new_var) != 0)
		return (free(new_var), 1);
	return (0);
}

/// @brief Changes the current directory to the specified path or to the
/// HOME directory if no path is provided.
/// @param argv The arguments, where argv[1] is the target directory.
/// @param env The environment array.
/// @param env_capacity The capacity of the environment array.
/// @return Returns 0 on success, 1 on failure.
int	ft_cd(char **argv, char ***env, int *env_capacity)
{
	char	oldpwd[1024];
	char	newpwd[1024];
	char	*path;

	if (!env || !*env || !env_capacity)
		return (1);
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (perror("cd minishell"), 1);
	path = argv[1];
	if (!path)
	{
		path = search_home(*env);
		if (!path)
			return (ft_putstr_fd("cd minishell: HOME not set\n", 2), 1);
	}
	if (chdir(path) != 0)
		return (perror("cd minishell"), 1);
	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		return (perror ("cd minishell"), 1);
	ft_upd_env(env, env_capacity, "OLDPWD", oldpwd);
	ft_upd_env(env, env_capacity, "PWD", newpwd);
	return (0);
}
