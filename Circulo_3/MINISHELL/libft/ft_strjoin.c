/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:14:51 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 12:58:04 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief Allocate (with malloc(3)) and returns a new string resulting 
/// from the concatenation of s1 and s2.
/// @param s1 first string to concatenate
/// @param s2 second string to concatenate
/// @return the new string or NULL if memory allocation failed
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	const char s1[] = "lorem ipsum";
	const char s2[] = " dolor sit amet";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/