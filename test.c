/*
(FD)(OPEN)Abrir el FILE y darle un fd,
(READ)Leer la línea correspondiente (hasta \n),
(COPY/JOIN)Copiar / Guardar la línea en una nueva variable (buffer),
(CLOSE)Cerrar el FILE
Devolver la línea.
*/
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
	fd = open("test.txt", O_CREAT | O_WRONLY, 0644); // Open in create / writte-only mode and full permissions
	if (fd == -1)
	{
		printf("Error opening file");
		free(buffer);
		return (1);
	}
	if (write(fd, "Hello, World!\n", BUFFER_SIZE) == -1)
	{
		printf("Error writing to file");
		close (fd);
		free(buffer);
		return(1);
	}
	close(fd);

    fd = open("test.txt", O_RDONLY, 0400); // Open in read-only mode and read permissions only
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