/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_operations.c                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:06:52 by dasanche          #+#    #+#             */
/*   Updated: 2026/01/13 12:06:52 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Opens and truncates a file to replicate bash behavior
/// @param filename The file to open and truncate
/// @return 0 on success, -1 on error
int	open_and_truncate_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	close(fd);
	return (0);
}

/// @brief Opens a file in append mode to replicate bash behavior
/// @param filename The file to open in append mode
/// @return 0 on success, -1 on error
int	open_append_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	close(fd);
	return (0);
}
