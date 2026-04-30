/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:35:21 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/30 13:56:52 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i > 0)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == (unsigned char) c)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char	s[] = "bonjour";

	printf ("%s\n", strrchr(s, '\0'));
	printf ("%s\n", ft_strrchr(s, '\0'));
	return (0);
}
*/
