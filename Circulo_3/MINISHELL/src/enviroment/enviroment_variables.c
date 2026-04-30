/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:46:33 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/04 19:37:01 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Expands variables in a token value, replacing special variables
/// like $? and $$, and environment variables.
/// @param value The input string containing variables to expand.
/// @param env The environment variables array.
/// @param last_status The last command's exit status, used for $? expansion.
/// @param shell_pid The shell's process ID, used for $$ expansion.
/// @return The expanded string with variables replaced.
char	*exp_tok_val(char *value, char **env, int last_status,
		int shell_pid)
{
	int				i;
	t_exp_ctx		ctx;
	t_minishell		shell;

	i = 0;
	ctx.j = 0;
	ctx.env = env;
	ctx.res = init_expansion_buffer(value, &ctx.cap);
	if (!ctx.res)
		return (NULL);
	shell.env = env;
	shell.ret_val = last_status;
	shell.shell_pid = shell_pid;
	while (value[i])
	{
		if (value[i] == '$')
			ctx.res = process_dollar_token(value, &i, &ctx, &shell);
		else
			ctx.res = append_char(ctx.res, &ctx.j, &ctx.cap, value[i++]);
		if (!ctx.res)
			return (NULL);
	}
	ctx.res[ctx.j] = '\0';
	return (ctx.res);
}

/// @brief Expands variables in heredoc content, replacing special variables
/// like $?, $$, and environment variables.
/// @param value The input string containing variables to expand.
/// @param hd_ctx Heredoc context with env, last_status, and shell_pid.
/// @return The expanded string with variables replaced.
char	*expand_heredoc_content(char *value, t_heredoc_ctx *hd_ctx)
{
	int			i;
	t_exp_ctx	ctx;

	i = 0;
	ctx.j = 0;
	ctx.env = hd_ctx->env;
	ctx.res = init_expansion_buffer(value, &ctx.cap);
	if (!ctx.res)
		return (NULL);
	while (value[i])
	{
		if (value[i] == '$')
			ctx.res = process_dollar_heredoc(value, &i, &ctx, hd_ctx);
		else
			ctx.res = append_char(ctx.res, &ctx.j, &ctx.cap, value[i++]);
		if (!ctx.res)
			return (NULL);
	}
	ctx.res[ctx.j] = '\0';
	return (ctx.res);
}
