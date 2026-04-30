/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:01:27 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:01:27 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Prints arguments with spaces between them
/// @param args The array of arguments to print
/// @param start_index The index to start printing from
static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

/// @brief Implements the `echo` built-in command, which prints
/// arguments to the standard output.
/// @param args The arguments passed to the echo command.
/// @return Returns 0 on success.
int	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!args || !args[0])
		return (0);
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0 && args[i][2] == '\0')
	{
		new_line = 0;
		i++;
	}
	if (!args[i])
	{
		if (new_line)
			ft_putchar_fd('\n', 1);
		return (0);
	}
	print_echo_args(args, i);
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
