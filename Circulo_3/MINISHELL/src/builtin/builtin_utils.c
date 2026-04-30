/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:01:13 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:01:13 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Searches for the HOME environment variable in the environment array.
/// @param env The environment array.
/// @return Returns a pointer to the value of the HOME variable,
/// or NULL if not found.
char	*search_home(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/// @brief Checks if the provided string is a valid environment variable
/// name.
/// @param s The string to check.
/// @return Returns 1 if valid, 0 otherwise.
int	name_var_check(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/// @brief Sorts an array of strings (bubble sort)
/// @param sorted The array to sort
/// @param count The number of elements in the array
void	sort_env_array(char **sorted, int count)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		x = 0;
		while (x < count - 1 - i)
		{
			if (ft_strncmp(sorted[x], sorted[x + 1],
					ft_strlen(sorted[x]) + 1) > 0)
			{
				tmp = sorted[x];
				sorted[x] = sorted[x + 1];
				sorted[x + 1] = tmp;
			}
			x++;
		}
		i++;
	}
}

/// @brief Prints a single environment variable in export format
/// @param var The environment variable string to print
void	print_export_var(char *var)
{
	int	x;

	x = 0;
	ft_printf("declare -x ");
	while (var[x])
	{
		if (var[x] == '=')
		{
			ft_printf("=\"%s\"", &var[x + 1]);
			break ;
		}
		ft_printf("%c", var[x]);
		x++;
	}
	ft_printf("\n");
}

/// @brief Prints the current environment variables in a sorted order,
/// formatted as `declare -x VAR="value"`.
/// @param env The environment array.
void	ft_export_print(char **env)
{
	int		i;
	int		count;
	char	**sorted;

	count = 0;
	while (env[count])
		count++;
	sorted = malloc(sizeof(char *) * count);
	if (!sorted)
		return ;
	i = 0;
	while (i < count)
	{
		sorted[i] = env[i];
		i++;
	}
	sort_env_array(sorted, count);
	i = 0;
	while (i < count)
	{
		print_export_var(sorted[i]);
		i++;
	}
	free(sorted);
}
