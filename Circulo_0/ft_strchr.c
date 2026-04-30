/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:43 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:14:52 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int	main(void)
{
	const char	s[] = "tripouille";
	printf("Antes de strchr: %s\n", s);
	printf("Despues de strchr: %s\n", ft_strchr(s, 't' + 256));
	printf("Antes de strchr: %s\n", s);
	printf("Despues de strchr: %s", strchr(s, 't' + 256));
	return (0);
}
*/