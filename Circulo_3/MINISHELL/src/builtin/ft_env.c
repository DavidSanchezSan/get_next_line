/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:01:41 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:01:41 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Prints the environment variables.
/// @param env The environment array.
/// @param argc The argument count.
/// @param argv The argument vector.
/// @return Returns 0 on success, 127 if an invalid argument is provided.
int	ft_env(char **env, int argc, char **argv)
{
	int	i;

	if (argc > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (!env)
		return (0);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
			ft_putstr_fd("_=/usr/bin/env\n", 1);
		else if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
