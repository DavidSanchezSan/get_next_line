/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:55:05 by egarcia2          #+#    #+#             */
/*   Updated: 2025/10/21 17:39:13 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief split a string into an array of words.
/// Allocate (with malloc(3)) and returns an array of strings obtained 
/// by splitting s with the character c, used as delimiter.
/// The returned array must be NUL-terminated.
/// @param s string to split
/// @param c delimiter character
/// @return an array of strings resulting from the splitting of s or 
/// NULL if the memory allocation failed.
static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	z;
	int		in_word;

	i = 0;
	z = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (in_word == 0)
			{
				z++;
				in_word = 1;
			}
		}
		else
			(in_word = 0);
		i++;
	}
	return (z);
}

static size_t	ft_count_letters(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && (s[i] != c))
		i++;
	return (i);
}

static char	*ft_allocate_words(const char *s, char c)
{
	size_t	len_letters;
	char	*dest;

	len_letters = ft_count_letters(s, c);
	dest = malloc((len_letters + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, len_letters + 1);
	return (dest);
}

static void	ft_free_memory(char **index, int j)
{
	while (j >= 0)
	{
		if (index[j] != NULL)
			free(index[j]);
		j--;
	}
	free(index);
}

char	**ft_split(char const *s, char c)
{
	char	**index;
	size_t	i;
	size_t	j;

	i = 0;
	j = -1;
	if (s == NULL)
		return (NULL);
	index = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!index)
		return (NULL);
	while (++j < ft_count_words(s, c))
	{
		while (s[i] == c)
			i++;
		index[j] = ft_allocate_words(&s[i], c);
		if (!index[j])
		{
			ft_free_memory(index, j);
			return (NULL);
		}
		i += ft_count_letters(&s[i], c);
	}
	index[j] = NULL;
	return (index);
}

/*
int	main(void)
{
	const char	*s = "hola como estas";
	char		c;
	char		**new;
	int			i;

	c = ' ';
	new = ft_split(s, c);
	i = 0;
	while (new[i])
	{
		printf("%s\n", new[i]);
		++i;
	}
	return (0);
}
*/