/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_advance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:02:11 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/23 20:10:32 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Advances the index over adjacent parts of a token, including
/// quoted and unquoted sections.
/// @param input The input string being tokenized.
/// @param i The current index within the input string.
/// @param array The token array being constructed.
/// @param quote The type of quote encountered (single or double).
/// @return The index just after the closing quote, or -1 if an error occurs.
static int	skip_quoted(char *input, int i, t_token_array *array, char quote)
{
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		ft_putstr_fd("ERROR: unclosed quote\n", 2);
		free_tokens(array);
		return (-1);
	}
	return (i + 1);
}

/// @brief Advances the index over an unquoted section of a token.
/// @param input The input string being tokenized.
/// @param i The current index within the input string.
/// @return The index of the first character that no longer belongs
/// to the unquoted part.
static int	skip_unquoted(char *input, int i)
{
	while (input[i] && !is_space(input[i]) && !is_operator(input[i])
		&& !is_quote(input[i]))
		i++;
	return (i);
}

/// @brief Advances the index over adjacent parts of a token,
/// including quoted and unquoted sections.
/// @param input The input string being tokenized.
/// @param i The current index within the input string.
/// @param array The token array being constructed.
/// @return The index just after the closing quote, or -1 if an error occurs.
static int	skip_adjacent_parts(char *input, int i, t_token_array *array)
{
	char	quote;

	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			i = skip_quoted(input, i, array, quote);
			if (i == -1)
				return (-1);
		}
		else
			i = skip_unquoted(input, i);
	}
	return (i);
}

/// @brief Advances the index in the input string to the end of the
/// current token, handling quoted and unquoted sections.
/// @param input The input string being tokenized.
/// @param i The current index within the input string.
/// @param array The token array being constructed.
/// @return The index just after the end of the current token,
// or -1 if an error occurs.
int	advance_index(char *input, int i, t_token_array *array)
{
	char	quote;

	if (is_operator(input[i]))
	{
		if ((input[i] == '<' || input[i] == '>') && input[i + 1] != '\0'
			&& input[i + 1] == input[i])
			return (i + 2);
		return (i + 1);
	}
	if (is_quote(input[i]))
	{
		quote = input[i++];
		i = skip_quoted(input, i, array, quote);
		if (i == -1)
			return (-1);
	}
	i = skip_unquoted(input, i);
	return (skip_adjacent_parts(input, i, array));
}
