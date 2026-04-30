/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:52:49 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/10 01:21:51 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Adds a new token to the token array, resizing the array if necessary.
/// @param array The token array to which the token will be added.
/// @param token_value The string value of the token to add.
/// @param quote The type of quote associated with the token (none,
/// single, or double).
/// @return 1 if the token was added successfully, 0 on error.
int	add_token(t_token_array *array, char *token_value,
	t_quote_type quote)
{
	int		new_capacity;
	t_token	*new_tokens;

	if (array->size >= array->capacity)
	{
		new_capacity = array->capacity * 2;
		new_tokens = malloc(new_capacity * sizeof(t_token));
		if (!new_tokens)
			return (0);
		ft_memcpy(new_tokens, array->tokens, array->size * sizeof(t_token));
		free(array->tokens);
		array->tokens = new_tokens;
		array->capacity = new_capacity;
	}
	array->tokens[array->size].value = ft_strdup(token_value);
	if (!array->tokens[array->size].value)
		return (0);
	array->tokens[array->size].type = classify_token_type(token_value);
	array->tokens[array->size].quote = quote;
	array->size++;
	return (1);
}

/// @brief Initializes token array with values and allocates memory for tokens.
/// @param array The token array to initialize.
static void	init_token_array(t_token_array *array)
{
	array->size = 0;
	array->capacity = 64;
	array->tokens = malloc(array->capacity * sizeof(t_token));
	if (!array->tokens)
	{
		ft_putstr_fd("ERROR: malloc failed\n", 2);
		array->tokens = NULL;
		return ;
	}
}

/// @brief Processes a token from the input string, extracts its value,
///classifies its type, and adds it to the token array.
/// @param array The token array to which the token will be added.
/// @param input The input string being tokenized.
/// @param i Pointer to the current index in the input string; updated to
/// the end of the processed token.
/// @param shell Minishell struct containing environment and state information.
/// @return 1 if the token was processed successfully, 0 on error.
static int	process_token(t_token_array *array, char *input, int *i,
	t_minishell *shell)
{
	int		start;
	int		end;
	char	*token_value;

	start = *i;
	end = advance_index(input, *i, array);
	if (end == -1)
		return (free_tokens(array), 0);
	token_value = ft_substr(input, start, end - start);
	if (!token_value)
		return (free_tokens(array), 0);
	if (!extract_and_add_token(array, token_value, shell))
	{
		free(token_value);
		return (free_tokens(array), 0);
	}
	free(token_value);
	*i = end;
	return (1);
}

/// @brief Tokenizes the input string into an array of tokens.
/// @param array The token array to store the generated tokens.
/// @param input The input string to tokenize.
/// @param shellMinishell struct containing environment and state information.
/// @return 1 if tokenization is successful, 0 on error.
int	tokenize_input(t_token_array *array, char *input, t_minishell *shell)
{
	int	i;

	i = 0;
	init_token_array(array);
	if (!array->tokens)
		return (0);
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (!process_token(array, input, &i, shell))
			return (0);
	}
	return (1);
}
