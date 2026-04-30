/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:46:33 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/04 19:37:01 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Grows the buffer size for variable expansion when needed
/// @param old The old buffer
/// @param used The number of bytes used in the old buffer
/// @param capacity Pointer to the current capacity of the buffer
/// @return The new buffer with increased capacity, or NULL on failure
char	*grow_buffer(char *old, int used, size_t *capacity)
{
	char	*new;
	size_t	new_capacity;

	new_capacity = *capacity * 2;
	if (new_capacity > MAX_EXPANSION_SIZE)
		new_capacity = MAX_EXPANSION_SIZE;
	if (new_capacity == *capacity)
		return (old);
	new = malloc(new_capacity);
	if (!new)
		return (free(old), NULL);
	ft_memcpy(new, old, used);
	free(old);
	*capacity = new_capacity;
	return (new);
}

/// @brief Appends a character to the result buffer, growing if needed
/// @param res Pointer to result buffer
/// @param j Pointer to current position in buffer
/// @param cap Pointer to buffer capacity
/// @param c Character to append
/// @return Updated buffer or NULL on error
char	*append_char(char *res, size_t *j, size_t *cap, char c)
{
	char	*new_res;

	if (*j + 1 >= *cap)
	{
		if (*cap >= MAX_EXPANSION_SIZE)
			return (free(res), NULL);
		new_res = grow_buffer(res, *j, cap);
		if (!new_res)
			return (free(res), NULL);
		res = new_res;
	}
	res[(*j)++] = c;
	return (res);
}

/// @brief Appends a string to the result buffer, growing if needed
/// @param res Pointer to result buffer
/// @param j Pointer to current position in buffer
/// @param cap Pointer to buffer capacity
/// @param str String to append
/// @return Updated buffer or NULL on error
char	*append_string(char *res, size_t *j, size_t *cap, char *str)
{
	size_t	len;
	char	*new_res;

	len = ft_strlen(str);
	while (*j + len >= *cap)
	{
		if (*cap >= MAX_EXPANSION_SIZE)
			return (free(res), NULL);
		new_res = grow_buffer(res, *j, cap);
		if (!new_res)
			return (free(res), NULL);
		res = new_res;
		if (*cap > MAX_EXPANSION_SIZE)
			*cap = MAX_EXPANSION_SIZE;
	}
	ft_memcpy(res + *j, str, len);
	*j += len;
	return (res);
}

/// @brief Expands $$ to shell PID
/// @param res Result buffer
/// @param j Current position
/// @param cap Buffer capacity
/// @param shell_pid Shell process ID
/// @return Updated buffer or NULL on error
char	*expand_double_dollar(char *res, size_t *j, size_t *cap, int shell_pid)
{
	char	*pid_str;
	char	*new_res;

	pid_str = ft_itoa(shell_pid);
	if (!pid_str)
		return (free(res), NULL);
	new_res = append_string(res, j, cap, pid_str);
	free(pid_str);
	return (new_res);
}

/// @brief Extracts variable name and expands its value
/// @param value Input string
/// @param i Pointer to current position
/// @param env Environment variables
/// @return Expanded value or empty string
char	*extract_var_value(char *value, int *i, char **env)
{
	int		start;
	char	*name;
	char	*env_val;

	start = *i;
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	name = ft_substr(value, start, *i - start);
	if (!name)
		return (NULL);
	env_val = get_variable_value(env, name);
	free(name);
	if (!env_val)
		return (ft_strdup(""));
	return (env_val);
}
