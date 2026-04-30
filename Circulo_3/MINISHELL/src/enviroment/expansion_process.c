/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:46:33 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/04 19:37:01 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Expands $? to last exit status
/// @param res Result buffer
/// @param j Current position
/// @param cap Buffer capacity
/// @param last_status Exit status value
/// @return Updated buffer or NULL on error
char	*exp_quest_mark(char *res, size_t *j, size_t *cap,
		int last_status)
{
	char	*status;
	char	*new_res;

	status = ft_itoa(last_status);
	if (!status)
		return (free(res), NULL);
	new_res = append_string(res, j, cap, status);
	free(status);
	return (new_res);
}

/// @brief Processes dollar sign expansion for token values
/// @param value Input string
/// @param i Pointer to position
/// @param ctx Expansion context
/// @param shell Shell structure with env and status
/// @return Updated buffer or NULL
char	*process_dollar_token(char *value, int *i, t_exp_ctx *ctx,
		t_minishell *shell)
{
	char	*env_val;

	(*i)++;
	if (value[*i] == '?')
	{
		ctx->res = exp_quest_mark(ctx->res, &ctx->j, &ctx->cap, shell->ret_val);
		(*i)++;
	}
	else if (value[*i] == '$')
	{
		ctx->res = expand_double_dollar(ctx->res, &ctx->j, &ctx->cap,
				shell->shell_pid);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
	{
		env_val = extract_var_value(value, i, ctx->env);
		if (!env_val)
			return (free(ctx->res), NULL);
		ctx->res = append_string(ctx->res, &ctx->j, &ctx->cap, env_val);
		free(env_val);
	}
	else
		ctx->res = append_char(ctx->res, &ctx->j, &ctx->cap, '$');
	return (ctx->res);
}

/// @brief Handles variable extraction in heredoc
/// @param value Input string
/// @param i Pointer to position
/// @param ctx Expansion context
/// @return Updated buffer or NULL
static char	*handle_heredoc_var(char *value, int *i, t_exp_ctx *ctx)
{
	char	*env_val;

	env_val = extract_var_value(value, i, ctx->env);
	if (!env_val)
		return (free(ctx->res), NULL);
	ctx->res = append_string(ctx->res, &ctx->j, &ctx->cap, env_val);
	if (!ctx->res)
		return (free(env_val), NULL);
	free(env_val);
	return (ctx->res);
}

/// @brief Processes dollar sign expansion for heredoc content
/// @param value Input string
/// @param i Pointer to position
/// @param ctx Expansion context
/// @param hd_ctx Heredoc context with env, status, and pid
/// @return Updated buffer or NULL
char	*process_dollar_heredoc(char *value, int *i,
		t_exp_ctx *ctx, t_heredoc_ctx *hd_ctx)
{
	(*i)++;
	if (value[*i] == '?')
	{
		ctx->res = exp_quest_mark(ctx->res, &ctx->j, &ctx->cap,
				hd_ctx->last_status);
		(*i)++;
	}
	else if (value[*i] == '$')
	{
		ctx->res = expand_double_dollar(ctx->res, &ctx->j, &ctx->cap,
				hd_ctx->shell_pid);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
		ctx->res = handle_heredoc_var(value, i, ctx);
	else
		ctx->res = append_char(ctx->res, &ctx->j, &ctx->cap, '$');
	return (ctx->res);
}

/// @brief Initializes expansion buffer
/// @param value Input string
/// @return Allocated buffer or NULL
char	*init_expansion_buffer(char *value, size_t *cap)
{
	char	*res;

	*cap = ft_strlen(value) + 1;
	if (*cap > MAX_EXPANSION_SIZE)
		*cap = MAX_EXPANSION_SIZE;
	res = malloc(*cap);
	return (res);
}
