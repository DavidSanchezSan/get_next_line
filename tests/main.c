// #include "get_next_line_bonus.h"

// int	main(int argc, char *argv[])
// {
//     if (argc != 4)
//     {
//         printf("Error con los argumentos");
//         return (1);
//     }
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		count_lines;
// 	char	*str;

// 	count_lines = 0;
// 	fd1 = open(argv[1], O_RDONLY);
// 	fd2 = open(argv[2], O_RDONLY);
// 	fd3 = open(argv[3], O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		printf("Error de apertura");
// 		return (1);
// 	}
// 	if (fd2 == -1)
// 	{
// 		printf("Error de apertura");
// 		return (1);
// 	}
// 	if (fd3 == -1)
// 	{
// 		printf("Error de apertura");
// 		return (1);
// 	}
// 	str = "Wow";
// 	while (str != NULL)
// 	{
// 		str = get_next_line(fd1);
// 		printf("%s\n", str);
// 		free(str);
// 		str = get_next_line(fd2);
// 		printf("%s\n", str);
// 		free(str);
// 		str = get_next_line(fd3);
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }

/*###################################################################################################################*/

// #include "get_next_line.h"
// int	main(void)
// {
// 	int		fd;
// 	int		count_lines;
// 	char	*str;

// 	count_lines = 0;
// 	fd = open("/home/dasanche/projects/tests/test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error de apertura");
// 		return (1);
// 	}
// 	str = "";
// 	while (str != NULL)
// 	{
// 		str = get_next_line(fd);
// 		count_lines++;
// 		printf("%d	%s", count_lines, str);
// 		free(str);
// 	}
// 	printf("\n       %s", str);
// 	close(fd);
// 	return (0);
// }