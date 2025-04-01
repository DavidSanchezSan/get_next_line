/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/04/01 15:46:03 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_free(char *buffer, char *stored)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(stored, buffer);
	free(stored);
	stored = ft_strdup(temp);
	free(temp);
	temp = NULL;
	return (stored);
}

static char	*ft_read_line(int *fd, int *bytes_read, char *buffer, char *stored)
{
	while (*bytes_read > 0)
	{
		*bytes_read = read(*fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (NULL);
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
		line = ft_strdup(*stored);
		free(*stored);
		*stored = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stored;
	char		*line;
	int			bytes_read;

	line = NULL;
	bytes_read = 1;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	stored = ft_read_line(&fd, &bytes_read, buffer, stored);
	if (!stored)
		return (free(buffer), stored = NULL, NULL);
	line = find_line(&stored, bytes_read);
	free(buffer);
	buffer = NULL;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	int		count_lines;
// 	char	*str;

// 	count_lines = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error de apertura");
// 		return (1);
// 	}
// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		count_lines++;
// 	}
// 	printf("%s", str);
// 	printf("\n%d\n", count_lines);
// 	close(fd);
// 	return (0);
// }
