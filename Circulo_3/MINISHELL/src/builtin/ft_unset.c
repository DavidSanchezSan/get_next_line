/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:03:35 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:03:35 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Unsets (removes) an environment variable from the environment array.
/// @param var The name of the variable to unset.
/// @param env The environment array.
/// @return 0 on success, 1 on failure.
int	ft_unset(char *var, char **env)
{
	int	i;
	int	j;

	if (!var || !env)
		return (1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& (env[i][ft_strlen(var)] == '='
			|| env[i][ft_strlen(var)] == '\0'))
		{
			free(env[i]);
			j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}
