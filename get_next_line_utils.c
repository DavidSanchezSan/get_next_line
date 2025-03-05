/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:14 by dasanche          #+#    #+#             */
/*   Updated: 2025/03/05 16:17:23 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

// Function that returns the length of a string

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x] != '\0')
	{
		x++;
	}
	return (x);
}

// Reserves with malloc and returns a new string,
// formed by the concatenation of ‘s1’ and ‘s2’.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;

	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_string, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	new_string[ft_strlen(new_string)] = '\0';
	return (new_string);
}
/* Function that erases the data in the n bytes of the memory starting
at the location pointed to by s, by writing zeros (bytes containing '\0')
to that area. */

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		ptr[x] = '\0';
		x++;
	}
}
