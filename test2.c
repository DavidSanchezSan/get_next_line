#include "get_next_line.h"

int	main(void)
{
	int	fd;
	char *buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		printf("Faiiled memory alocation");
		return (-1);
	}

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error reopening file");
        free(buffer);
        return (1);
	}
	if (read(fd, buffer, BUFFER_SIZE) == -1)
	{
		printf("Error reading the file");
		close(fd);
		free(buffer);
		return(1);
	}
	buffer[BUFFER_SIZE] = '\0';
	printf("%s", buffer);
	close(fd);
	free(buffer);
	return(0);
}