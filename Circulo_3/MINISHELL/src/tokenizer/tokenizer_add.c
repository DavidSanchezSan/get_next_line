/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:02:11 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/08 17:47:31 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Resizes the token array when capacity is reached.
/// @param array The token array to resize.
/// @return 1 if successful, 0 on error.
static int	resize_token_array(t_token_array *array)
{
	int		new_capacity;
	t_token	*new_tokens;

	new_capacity = array->capacity * 2;
	new_tokens = malloc(new_capacity * sizeof(t_token));
	if (!new_tokens)
		return (0);
	ft_memcpy(new_tokens, array->tokens, array->size * sizeof(t_token));
	free(array->tokens);
	array->tokens = new_tokens;
	array->capacity = new_capacity;
	return (1);
}

/// @brief Adds a new token to the token array, resizing the array if necessary.
/// @param array The token array to which the token will be added.
/// @param token_value The string value of the token to add.
/// @param quote The type of quote associated with the token (none,
/// single, or double).
/// @return 1 if the token was added successfully, 0 on error.
static int	add_token(t_token_array *array, char *token_value,
	t_quote_type quote)
{
	if (array->size >= array->capacity)
	{
		if (!resize_token_array(array))
			return (0);
	}
	array->tokens[array->size].value = ft_strdup(token_value);
	if (!array->tokens[array->size].value)
		return (0);
	array->tokens[array->size].type = classify_token_type(token_value);
	if (quote != QUOTE_NONE)
		array->tokens[array->size].type = TOKEN_WORD;
	array->tokens[array->size].quote = quote;
	array->size++;
	return (1);
}

/// @brief Appends a part of the token to the result string, 
/// optionally expanding environment variables.
/// @param result The accumulated token string.
/// @param part The newly extracted substring of the token.
/// @param expand Indicates whether to expand (1) or not (0).
/// @param shell Structure to access env and ret_val
/// @return 1 if the concatenation is successful, 0 if it fails.
int	append_part(char **result, char *part, int expand,
	t_minishell *shell)
{
	char	*exp;
	char	*temp;

	exp = NULL;
	if (expand)
	{
		exp = exp_tok_val(part, shell->env, shell->ret_val, shell->shell_pid);
		if (!exp)
			exp = ft_strdup("");
		temp = ft_strjoin(*result, exp);
		free(exp);
	}
	else
		temp = ft_strjoin(*result, part);
	free(part);
	if (!temp)
		return (0);
	free(*result);
	*result = temp;
	return (1);
}

/// @brief Processes and builds the token result string from raw token value
/// @param token_value The raw token string to process.
/// @param shell Pointer to the minishell structure.
/// @param had_quotes Pointer to store whether quotes were found.
/// @return The processed result string, or NULL on failure.
static char	*process_token_string(char *token_value, t_minishell *shell,
	int *had_quotes)
{
	char	*result;
	int		i;

	i = 0;
	*had_quotes = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (token_value[i])
	{
		if (is_quote(token_value[i]) && ++(*had_quotes)
			&& !process_quoted_part(token_value, &i, &result, shell))
			return (free(result), NULL);
		else if (!is_quote(token_value[i])
			&& !process_unquoted_section(token_value, &i, &result, shell))
			return (free(result), NULL);
	}
	return (result);
}

/// @brief Extracts the final token value from the raw token string,
// handling quoted and unquoted sections, and adds it to the token array.
/// @param array The token array to which the token will be added.
/// @param token_value The raw token string to process.
/// @param shell Pointer to the minishell structure.
/// @return 1 if the token was processed and added successfully, 0 on failure.
int	extract_and_add_token(t_token_array *array, char *token_value,
	t_minishell *shell)
{
	char			*result;
	int				had_quotes;
	t_quote_type	qt;

	result = process_token_string(token_value, shell, &had_quotes);
	if (!result)
		return (0);
	if (had_quotes)
		qt = QUOTE_SINGLE;
	else
		qt = QUOTE_NONE;
	if (!add_token(array, result, qt))
		return (free(result), 0);
	return (free(result), 1);
}
