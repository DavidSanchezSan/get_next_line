/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:02:14 by dasanche          #+#    #+#             */
/*   Updated: 2025/03/18 14:34:51 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function that fills the first n bytes of the memory area pointed to
// by s with the constant byte c.

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		ptr[x] = c;
		x++;
	}
	return (s);
}

// Function that allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero.
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	total = nmemb * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total);
	return (ptr);
}

// Function function returns a pointer to a new string which is a duplicate of
// the string s.  Memory for the new string is obtained with malloc, and can
// be freed with free.

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s);
	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}

// Function that returns a pointer to the first matched character
// or NULL if the character is not found.

char	*ft_strchr(const char *s, int c)
{
	char	a;

	a = (char)c;
	while (*s != '\0')
	{
		if (*s == a)
			return ((char *)s);
		s++;
	}
	if (a == '\0')
		return ((char *)s);
	return (NULL);
}

// Function that concatenate strings.

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	len_dst;
	size_t	len_src;

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

// Reserves and returns a substring of the string ‘s’.
// The substring starts from index ‘start’ and has a maximum length of ‘len’.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*subs;
	const char	*to_copy;

	if (s == NULL || start >= ft_strlen(s) || len <= 0)
		return (ft_calloc(1, sizeof(char)));
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (len + start > ft_strlen(s))
		subs = malloc((len) * sizeof(char));
	else
		subs = malloc((len + 1) * sizeof(char));
	to_copy = &s[start];
	if (subs == NULL)
		return (NULL);
	ft_memcpy(subs, to_copy, len);
	subs[len] = '\0';
	return (subs);
}

// Function that copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap.

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			x;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	x = 0;
	if (src == dest)
		return (dest);
	while (x < n)
	{
		ptr_dest[x] = ptr_src[x];
		x++;
	}
	return (ptr_dest);
}
