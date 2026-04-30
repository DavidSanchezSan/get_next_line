/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:37:26 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/07 15:44:15 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Strips all characters of a string ‘set’ from the beginning and from the end
of ‘s1’, until a character not belonging to ‘set’ is found. The resulting
string is returned with a malloc reservation.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	end = ft_strlen(s1) -1;
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start;
	return (ft_substr(s1, start, len + 1));
}

// int	main(void)
// {
// 	const char *s1 = "BABAholaBABA";
// 	const char *set = "BA";
// 	printf("String antes de strtrim: %s\n", s1);
// 	char *a = ft_strtrim(s1, set);
// 	printf("String tras strtrim: %s", a);
// 	return (0);
// }