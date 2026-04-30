/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:05:24 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:16:44 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that copies up to size - 1 characters from the
// NULL-terminated string src to dst, NULL-terminating the result.

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size == 0)
		return (ft_strlen(src));
	else
	{
		while (x < size - 1 && (src[x] != '\0'))
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = '\0';
		return (ft_strlen(src));
	}
}
/*
int	main(void)
{
	char	src[50] = "rrrrr";
	char	dst[50] = "";

	printf("%zu\n", ft_strlcpy(dst, src, 15));
	printf("%s", dst);
	return (0);
}
*/
/*
int	main(void)
{
	char	src[50] = "Hola mundo";
	char	dst[50];

	printf("%zu\n", strlcpy(dst,src,10));
	printf("%s",dst);
	return (0);
}
*/
