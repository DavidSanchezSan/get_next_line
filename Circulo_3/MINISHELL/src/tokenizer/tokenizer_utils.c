/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:20:24 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/07 18:20:24 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if the character is a whitespace character.
/// @param c The character to check.
/// @return 1 if the character is a whitespace (TRUE), 0 otherwise (FALSE).
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

/// @brief Checks if the character is operator that should be individual token
/// @param c The character to check.
/// @return 1 if the character is an operator (TRUE), 0 otherwise (FALSE).
int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/// @brief Checks if the character is a single or double quote.
/// @param c The character to check.
/// @return 1 if the character is a quote (TRUE), 0 otherwise (FALSE).
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/// @brief Frees all memory allocated for tokens
/// @param array The token array to free.
void	free_tokens(t_token_array *array)
{
	int	i;

	i = 0;
	if (!array->tokens)
		return ;
	while (i < array->size)
	{
		free(array->tokens[i].value);
		i++;
	}
	free(array->tokens);
	array->tokens = NULL;
	array->size = 0;
	array->capacity = 0;
}

/// @brief Classifies the type of a token based on its value.
/// @param value The text of the token.
/// @return The type of the token.
t_token_type	classify_token_type(char *value)
{
	if (ft_strncmp(value, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (TOKEN_HERE_DOC);
	else if (ft_strncmp(value, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(value, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(value, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	return (TOKEN_WORD);
}
