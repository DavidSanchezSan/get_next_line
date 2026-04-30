/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_add_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:02:11 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/08 17:47:31 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Processes a quoted part of the token, handling expansion
// for double quotes.
/// @param token_value The full token string being processed.
/// @param i Pointer to the current index within the token string.
/// @param result Double pointer to the accumulated token string.
/// @param shell Pointer to the minishell structure.
/// @return 1 if the part is processed successfully, 0 on failure.
int	process_quoted_part(char *token_value, int *i, char **result,
	t_minishell *shell)
{
	char	quote;
	int		part_start;
	char	*part;
	int		expand;

	quote = token_value[(*i)++];
	part_start = *i;
	while (token_value[*i] && token_value[*i] != quote)
		(*i)++;
	part = ft_substr(token_value, part_start, *i - part_start);
	if (!part)
		return (0);
	expand = (quote != '\'');
	if (!append_part(result, part, expand, shell))
		return (0);
	if (token_value[*i] == quote)
		(*i)++;
	return (1);
}

/// @brief Processes unquoted section and appends to result
/// @param token_value The full token string being processed.
/// @param i Pointer to the current index within the token string.
/// @param result Double pointer to the accumulated token string.
/// @param shell Pointer to the minishell structure.
/// @return 1 if successful, 0 on failure.
int	process_unquoted_section(char *token_value, int *i,
	char **result, t_minishell *shell)
{
	int		start;
	char	*part;

	start = *i;
	while (token_value[*i] && !is_quote(token_value[*i]))
		(*i)++;
	part = ft_substr(token_value, start, *i - start);
	if (!part)
		return (0);
	if (!append_part(result, part, 1, shell))
		return (0);
	return (1);
}
