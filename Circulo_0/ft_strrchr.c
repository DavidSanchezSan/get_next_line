/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:21:40 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:17:59 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that returns a pointer to the last matched character
// or NULL if the character is not found.

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			last = s;
		s++;
	}
	if (*s == '\0')
	{
		if ((unsigned char)c == '\0')
		{
			last = s;
			return ((char *)last);
		}
		return ((char *)last);
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	s[50] = "teste";

// 	printf("Antes de strrchr: %s\n", s);
// 	printf("Despues de strrchr: %s\n", ft_strrchr(s, 1024));
// 	printf("Antes de strrchr: %s\n", s);
// 	printf("Despues de strrchr: %s", strrchr(s, 1024));
// 	return (0);
// }