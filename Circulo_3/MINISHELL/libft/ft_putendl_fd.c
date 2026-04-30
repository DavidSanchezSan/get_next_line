/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:31 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/30 13:56:47 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	new_line;

	i = 0;
	new_line = '\n';
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		++i;
	}
	write(fd, &new_line, 1);
}
/*
int	main(void)
{
	char	*str;

	str = "Hola mundo";
	ft_putendl_fd(str, 1);
	return (0);
}
*/
