
#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static char *stored;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *line;
    
    line = NULL;
    if (fd < 0)
        return NULL;
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
        return (NULL);
    buffer[bytes_read] = '\0';
    if (stored == NULL)
    {
        stored = malloc(bytes_read + 1);
        if (stored == NULL) 
            return (NULL);
        ft_strlcpy(stored, buffer, bytes_read + 1);
    }
    else 
    {
        char *temp = ft_strjoin(stored, buffer);
        free(stored);
        stored = temp;
    }
    line = stored;
    stored = NULL;
    return(line);
}

int main(void) 
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file");
        return (1);
    }

    char *line = get_next_line(fd);
    if (line)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return(0);
}