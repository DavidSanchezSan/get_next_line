/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:02:52 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:02:52 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

/// @brief Searches for and updates an existing environment variable
/// @param env The environment array
/// @param new_var The variable to update
/// @param name_size The length of the variable name
/// @return 1 if found and updated, 0 if not found, -1 on error
static int	update_existing_var(char ***env, char *new_var, size_t name_size)
{
	int		i;
	char	*new_str;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], new_var, name_size)
			&& ((*env)[i][name_size] == '=' || (*env)[i][name_size] == '\0'))
		{
			new_str = ft_strdup(new_var);
			if (!new_str)
				return (-1);
			free((*env)[i]);
			(*env)[i] = new_str;
			return (1);
		}
		i++;
	}
	return (0);
}

/// @brief Expands the environment array and adds a new variable
/// @param env The environment array
/// @param new_var The new variable to add
/// @param env_capacity The capacity of the environment array
/// @param i The current size of the environment array
/// @return Returns 0 on success, 1 on failure
static int	expand_and_add_var(char ***env, char *new_var,
	int *env_capacity, int i)
{
	char	**new_env;
	int		x;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);
	x = 0;
	while (x < i)
	{
		new_env[x] = (*env)[x];
		x++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (free(new_env), 1);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	*env_capacity = i + 2;
	return (0);
}

/// @brief Adds a new environment variable or updates an
/// existing one in the environment array.
/// @param env The environment array.
/// @param new_var The new variable to add or update.
/// @param env_capacity The capacity of the environment array.
/// @return Returns 0 on success, 1 on failure.
int	add_var(char ***env, char *new_var, int *env_capacity)
{
	int		i;
	int		result;
	char	*equal_sign;
	size_t	name_size;

	equal_sign = ft_strchr(new_var, '=');
	if (equal_sign != NULL)
		name_size = (size_t)(equal_sign - new_var);
	else
		name_size = ft_strlen(new_var);
	result = update_existing_var(env, new_var, name_size);
	if (result)
		return (result == -1);
	i = 0;
	while ((*env)[i])
		i++;
	if (i + 1 < *env_capacity)
	{
		(*env)[i] = ft_strdup(new_var);
		if (!(*env)[i])
			return (1);
		return ((*env)[i + 1] = NULL, 0);
	}
	return (expand_and_add_var(env, new_var, env_capacity, i));
}

/// @brief Export built-in command, which sets environment
/// variables or prints the current environment.
/// @param args The arguments passed to the export command.
/// @param env The environment array.
/// @param env_capacity The capacity of the environment array.
/// @return Returns 0 on success, 1 on failure.
int	ft_export(char **args, char ***env, int *env_capacity)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
	{
		ft_export_print(*env);
		return (0);
	}
	while (args[i])
	{
		if (!name_var_check(args[i]))
		{
			ft_printf("minishell: export: '%s': not a valid identifier\n",
				args[i]);
			ret = 1;
		}
		else
			if (add_var(env, args[i], env_capacity))
				ret = 1;
		i++;
	}
	return (ret);
}
