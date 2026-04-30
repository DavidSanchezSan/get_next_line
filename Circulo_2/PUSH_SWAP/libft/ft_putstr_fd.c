/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:51:44 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:14:46 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that sends the string ‘s’ to the specified file descriptor.

void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		write (fd, &s[count], 1);
		count++;
	}
}

// int	main(void)
// {
// 	char str[] = "user_exe";
// 	ft_putstr_fd(str, 1);
// 	return (0);
// }
