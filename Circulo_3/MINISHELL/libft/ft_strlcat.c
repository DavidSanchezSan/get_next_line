/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:16:24 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 10:48:04 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = 0;
	len = ft_strlen(dst);
	i = len;
	if (size <= len || size == 0)
		return (size + ft_strlen(src));
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (len + ft_strlen(src));
}
/*
int	main(void)
{
	char	dest[6] = "Hola";
	const char	src[10] = " Mundo";
	size_t	len; 

	len = ft_strlcat(dest, src, 7);
	printf("%zu\n", len);
}
*/
