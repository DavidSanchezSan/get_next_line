/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:23:36 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:23:36 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Opens the output file for the given command and returns its fd.
/// @param cmd The command structure containing output file information.
/// @return The file descriptor of the opened output file, or -1 on failure.
int	open_outfile(t_command *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return (-1);
	if (cmd->append == 1)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

/// @brief Opens the input file for the given command and returns its fd.
/// @param cmd The command structure containing input file information.
/// @return The file descriptor of the opened input file, or -1 on failure.
int	open_infile(t_command *cmd)
{
	int	fd;

	if (!cmd->infile)
		return (-1);
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

/// @brief Creates the heredoc template filename
/// @param shell_pid The process ID of the shell
/// @param template Buffer to store the template path
/// @return 0 on success, -1 on failure
int	create_heredoc_template(int shell_pid, char *template)
{
	static int	counter;
	char		*counter_str;
	char		*pid_str;

	pid_str = ft_itoa(shell_pid);
	counter_str = ft_itoa(counter++);
	if (!counter_str || !pid_str)
	{
		free(counter_str);
		free(pid_str);
		return (-1);
	}
	ft_strlcpy(template, "/tmp/.heredoc_", 256);
	ft_strlcat(template, pid_str, 256);
	ft_strlcat(template, "_", 256);
	ft_strlcat(template, counter_str, 256);
	free(counter_str);
	free(pid_str);
	return (0);
}

/// @brief Processes and expands heredoc line if needed
/// @param line The line to process
/// @param cmd The command structure
/// @param hd_ctx Heredoc context with env, last_status, and shell_pid
/// @return The processed line, or NULL on failure
char	*process_heredoc_line(char *line, t_command *cmd,
		t_heredoc_ctx *hd_ctx)
{
	char	*expanded;

	if (!cmd->heredoc_quoted)
	{
		expanded = expand_heredoc_content(line, hd_ctx);
		free(line);
		return (expanded);
	}
	return (line);
}

/// @brief Checks if line matches heredoc delimiter
/// @param line The line to check
/// @param delimiter The heredoc delimiter
/// @return 1 if matches, 0 otherwise
int	is_heredoc_delimiter(char *line, char *delimiter)
{
	if (ft_strlen(line) == ft_strlen(delimiter)
		&& ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		return (1);
	return (0);
}
