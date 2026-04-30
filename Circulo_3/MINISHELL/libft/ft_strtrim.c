/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:22:32 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 13:08:26 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief  Allocate (with malloc(3)) and returns a copy of s1, 
/// without the characters specified in set at the beginning and the end of s1.
/// @param s1 string to trim
/// @param set  characters to trim
/// @return a trimmed copy of s1 or NULL if the memory allocation failed.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start;
	return (ft_substr(s1, start, len + 1));
}
/*
int	main(void)
{
	char const	*s1;
	char const	*set;

	s1 = "   hola   ";
	set = " ";
	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}
*/