/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:36:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/03/19 14:27:42 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line_test(int fd)
{
	char		*buffer;
	static char	*stored;
	char		*line;
	char		*temp;
	int			bytes_read;
	int			to_end;

	line = NULL;
	temp = NULL;
	bytes_read = 1;
	to_end = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		printf("Error de memoria");
		return (NULL);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			printf("Error de lectura");
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (stored == NULL && bytes_read == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (stored == NULL)
			stored = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stored, buffer);
			free(stored);
			stored = temp;
		}
		if (ft_strchr(stored, '\n') != NULL)
			break ;
	}
	if (ft_strchr(stored, '\n') != NULL)
	{
		while (stored[to_end] != '\n' && stored[to_end] != '\0')
			to_end++;
		line = ft_substr(stored, 0, to_end);
		temp = ft_substr(stored, to_end + 1, (ft_strlen(stored) - to_end - 1));
		free(stored);
		stored = temp;
	}
	else if (bytes_read == 0 && stored != NULL)
	{
		line = ft_strdup(stored);
		free(stored);
		stored = NULL;
	}
	free(buffer);
	return (line);
}

int	main(void)
{
	int fd;
	char *str;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error de apertura");
		return (1);
	}
	while ((str = get_next_line_test(fd)) != NULL)
	{
		printf("--------------------------------------------------------------\n");
		printf("%s\n", str);
		free(str);
	}
	close(fd);
	return (0);
}