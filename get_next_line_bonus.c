/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/04/07 13:43:01 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_free(char *buffer, char *stored)
{
	char	*temp;

	temp = ft_strjoin(stored, buffer);
	free(stored);
	return (temp);
}

static char	*ft_read_line(int *fd, int *bytes_read, char *buffer, char *stored)
{
	while (*bytes_read > 0)
	{
		*bytes_read = read(*fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(stored);
			stored = NULL;
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		if (stored == NULL && *bytes_read == 0)
			return (NULL);
		if (stored == NULL)
			stored = ft_strdup("");
		stored = join_free(buffer, stored);
		if (ft_strchr(stored, '\n') != NULL)
			break ;
	}
	return (stored);
}

static char	*cleanup_stored(char **stored, char *line)
{
	free(*stored);
	*stored = NULL;
	return (line);
}

static char	*find_line(char **stored, int bytes_read)
{
	char	*line;
	char	*temp;
	int		to_end;

	line = NULL;
	temp = NULL;
	to_end = 0;
	if (ft_strchr(*stored, '\n') != NULL)
	{
		while ((*stored)[to_end] != '\n' && (*stored)[to_end] != '\0')
			to_end++;
		line = ft_substr(*stored, 0, to_end + 1);
		temp = ft_substr(*stored, to_end + 1, ft_strlen(*stored) - to_end - 1);
		free(*stored);
		*stored = temp;
	}
	else if (bytes_read == 0 && *stored != NULL)
	{
		if ((*stored)[0] == '\0')
			return (cleanup_stored(stored, NULL));
		else
			return (line = ft_strdup(*stored), cleanup_stored(stored, line));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stored[1024];
	char		*line;
	int			bytes_read;

	line = NULL;
	bytes_read = 1;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	stored[fd] = ft_read_line(&fd, &bytes_read, buffer, stored[fd]);
	if (!stored[fd])
		return (free(buffer), stored[fd] = NULL, NULL);
	line = find_line(&stored[fd], bytes_read);
	free(buffer);
	buffer = NULL;
	return (line);
}
