/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:27:04 by egarcia2          #+#    #+#             */
/*   Updated: 2026/02/17 19:00:57 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Sets up signal handler for heredoc handling SIGINT + ignoring SIGQUIT
/// @param  void
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief Signal handler for SIGINT during heredoc input, sets signal + newline
/// @param sig The signal number received
void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

/// @brief Signal handler for cleanup.
/// @param sig The signal number received
void	cleanup_handler(int sig)
{
	(void)sig;
	exit(128 + sig);
}
