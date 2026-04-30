/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:02:36 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:14:27 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that sends the string ‘s’ to the
// specified file descriptor, followed by a jump line.

void	ft_putendl_fd(char *s, int fd)
{
	int		count;
	char	jump_line;

	count = 0;
	jump_line = '\n';
	while (s[count] != '\0')
	{
		write (fd, &s[count], 1);
		count++;
	}
	write (fd, &jump_line, 1);
}

// int	main(void)
// {
// 	char str[] = "user_exe";
// 	ft_putendl_fd(str, 1);
// 	return (0);
// }