/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:54:35 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/29 14:54:04 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	z;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[j])
		{
			z = i;
			while (z < len && big[z] == little[j] && little[j] != '\0')
			{
				z++;
				j++;
			}
			if (little[j] == '\0')
				return ((char *)&big[i]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	*big = "lorem ipsum dolor sit amet";
	const char	*little = "dolor";
	char		*ptr;

	ptr = strnstr(big, little, 15);
	printf ("%s\n", ptr);
	printf ("%s\n", ft_strnstr(big, little, 15));
	return (0);
}
*/