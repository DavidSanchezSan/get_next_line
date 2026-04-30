/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:48:40 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:16:36 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that concatenate strings.

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		x;
	size_t		len_dst;
	size_t		len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	x = len_dst;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	else
	{
		while (x < size - 1 && *src)
		{
			dst[x] = *src;
			x++;
			src++;
		}
		dst[x] = '\0';
		return (len_src + len_dst);
	}
}
/*
int	main(void)
{
	char	dst[50] = "Hola";
	const char	src[50] = "CCCCCAAAAAAAAA";

	printf("%zu\n", ft_strlcat(dst, src, -1));
	printf("%s\n", dst);
}
*/