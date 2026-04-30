/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:23:36 by dasanche          #+#    #+#             */
/*   Updated: 2026/02/21 10:59:15 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Reads heredoc content and writes to file descriptor
/// @param fd The file descriptor to write to
/// @param cmd The command structure
/// @param hd_ctx Heredoc context with env, last_status, and shell_pid
/// @return 0 on success, -1 on failure
static int	read_lines_to_fd(int fd, t_command *cmd, t_heredoc_ctx *hd_ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			if (line)
				free(line);
			return (-1);
		}
		if (!line)
			return (-1);
		if (is_heredoc_delimiter(line, cmd->heredoc_delimiter))
			return (free(line), 0);
		line = process_heredoc_line(line, cmd, hd_ctx);
		if (!line)
			return (-1);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

/// @brief Cleans up heredoc on error  
/// @param fd The file descriptor to close
/// @param template The template file path to unlink
static void	cleanup_heredoc_error(int fd, char *template)
{
	close(fd);
	unlink(template);
}

int	process_heredoc_now(t_command *cmd, t_minishell *shell)
{
	int				fd;
	int				read_fd;
	char			tmp[256];
	t_heredoc_ctx	hd_ctx;

	g_signal = 0;
	setup_heredoc_signals();
	hd_ctx.env = shell->env;
	hd_ctx.last_status = shell->ret_val;
	hd_ctx.shell_pid = shell->shell_pid;
	if (create_heredoc_template(shell->shell_pid, tmp) < 0)
		return (-1);
	fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (ft_putstr_fd("minishell: failed to create heredoc\n", 2), -1);
	if (read_lines_to_fd(fd, cmd, &hd_ctx) < 0)
		return (cleanup_heredoc_error(fd, tmp), signals_setup(), -1);
	close(fd);
	read_fd = open(tmp, O_RDONLY);
	unlink(tmp);
	signals_setup();
	if (read_fd < 0)
		return (-1);
	return (read_fd);
}
