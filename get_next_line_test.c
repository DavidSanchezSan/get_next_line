/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:36:18 by dasanche          #+#    #+#             */
/*   Updated: 2025/03/18 14:34:53 by dasanche         ###   ########.fr       */
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
		// printf("Bytes leídos: %d\n",bytes_read);
		// printf("Contenido del buffer: %s\n",buffer);
		if (stored == NULL)
			stored = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stored, buffer);
			free(stored);
			stored = temp;
		}
		// printf("Contenido de stored: %s\n",stored);
		if (ft_strchr(stored, '\n') != NULL)
			break ;
		// printf("Contenido de line: %s\n",line);
	}
	if (ft_strchr(stored, '\n') != NULL)
	{
		while (stored[to_end] != '\n'
			&& stored[to_end] != '\0')
			to_end++;
		line = ft_substr(stored, 0, to_end);
		temp = ft_substr(stored, to_end + 1, (ft_strlen(stored) - to_end));
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
	str = get_next_line_test(fd);
	printf("--------------------------------------------------------------\n");
	printf("%s\n", str);
	str = get_next_line_test(fd);
	printf("--------------------------------------------------------------\n");
	printf("%s\n", str);
	str = get_next_line_test(fd);
	printf("--------------------------------------------------------------\n");
	printf("%s\n", str);
	str = get_next_line_test(fd);
	printf("--------------------------------------------------------------\n");
	printf("%s\n", str);
	str = get_next_line_test(fd);
	printf("--------------------------------------------------------------\n");
	printf("%s\n", str);
	close(fd);
	return (0);
}