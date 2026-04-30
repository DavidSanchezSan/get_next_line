/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:28 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/04 19:25:52 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// // Function that reserves, using malloc, an array of strings resulting from
// // separating the string ‘s’ into substrings using the character ‘c’
// // as delimiter. The array must end with a NULL pointer.

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && (s[i - 1] != c) && (i != 0))
			count++;
		if ((s[i] != c) && (s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	count_letters(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			if (s[i] != c)
				return (count);
		}
		i++;
		count++;
	}
	return (count);
}

static void	free_array(char **new_array, int i)
{
	int	x;

	x = 0;
	while (i >= x)
	{
		free(new_array[i]);
		i--;
	}
	free(new_array);
}

static char	**alocate_words(int words, char **new_array, char c, char const *s)
{
	int	i;
	int	s_count;
	int	word_count;

	i = 0;
	s_count = 0;
	while (i < words)
	{
		word_count = 0;
		new_array[i] = malloc((count_letters(&s[s_count], c) + 1)
				* (sizeof(char)));
		if (!new_array[i])
		{
			free_array(new_array, i);
			return (NULL);
		}
		while (s[s_count] == c)
			s_count++;
		while (s[s_count] != c && s[s_count] != '\0')
			new_array[i][word_count++] = s[s_count++];
		new_array[i][word_count] = '\0';
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	new_array = malloc((words + 1) * (sizeof(char *)));
	if (!new_array)
		return (NULL);
	new_array = alocate_words(words, new_array, c, s);
	return (new_array);
}

// int	main(void)
// {
// 	const char s[] = "    Hola esto es una prueba    ";
// 	char **new_array;
// 	new_array = ft_split(s, ' ');
// 	printf("%s\n", new_array[0]);
// 	printf("%s\n", new_array[1]);
// 	printf("%s\n", new_array[2]);
// 	printf("%s\n", new_array[3]);
// 	printf("%s\n", new_array[4]);
// 	free(new_array);
// 	return (0);
// }
