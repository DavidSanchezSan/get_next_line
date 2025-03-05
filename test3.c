#include "get_next_line.h"

int	main(void)
{
	int	fd;
	static char *buffer;
	int bytes_read;
	char c;
	char c_read;

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		printf("Faiiled memory allocation");
		return (-1);
	}

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file");
        free(buffer);
        return (1);
	}

	while (bytes_read < BUFFER_SIZE)
    {
        c_read = read(fd, &c, 1);  // First, perform the read operation
        if (c_read == -1)
        {
            printf("Error reading the file\n");
            close(fd);
            free(buffer);
            return(1);
        }
        if (c_read <= 0)  // This checks for EOF or read error
            break;
        buffer[bytes_read++] = c;

        if (c == '\n')  // Stop reading if a newline is encountered
            break;
    }

	buffer[bytes_read] = '\0';
	printf("%s", buffer);
	close(fd);
	free(buffer);
	return(0);
}
