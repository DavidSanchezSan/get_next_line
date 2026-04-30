/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:02:36 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:02:36 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/// @brief Parses the sign from the string and returns starting index
/// @param str The string to parse
/// @param sign Pointer to store the sign (1 or -1)
/// @return The index where digits start
static int	get_sign_and_start(char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

/// @brief Converts digit string to unsigned long long with overflow check
/// @param str The digit string
/// @param start Starting index
/// @param limit The overflow limit
/// @param num Pointer to store result
/// @return 1 if valid conversion, 0 if overflow or invalid digit
static int	convert_to_ull(char *str, int start, unsigned long long limit,
		unsigned long long *num)
{
	int	i;
	int	digit;

	i = start;
	*num = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		digit = str[i] - '0';
		if (*num > limit / 10
			|| (*num == limit / 10 && (unsigned long long)digit > limit % 10))
			return (0);
		*num = *num * 10 + digit;
		i++;
	}
	return (1);
}

/// @brief Validates that str represents a valid long long value.
/// @param str The string to validate.
/// @param result Pointer to store the parsed long long value.
/// @return Returns 1 if valid, 0 if not.
static int	ft_is_valid_ll(char *str, long long *result)
{
	unsigned long long	num;
	unsigned long long	limit;
	int					sign;
	int					start;

	start = get_sign_and_start(str, &sign);
	if (sign == 1)
		limit = 9223372036854775807ULL;
	else
		limit = 9223372036854775808ULL;
	if (!convert_to_ull(str, start, limit, &num))
		return (0);
	if (sign == 1)
		*result = (long long)num;
	else
		*result = -(long long)num;
	return (1);
}

/// @brief Implements the `exit` built-in command, which exits
/// the shell with a given status.
/// @param args The arguments passed to the exit command.
/// @param current_status The current exit status of the shell.
/// @return Returns the exit status code or -1 if there is an error
/// (e.g., too many arguments).
int	ft_exit(char **args, int current_status)
{
	long long	val;
	int			exit_status;

	if (!args[1])
		return (current_status);
	if (!ft_is_valid_ll(args[1], &val))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	exit_status = (int)((val % 256 + 256) % 256);
	return (exit_status);
}
