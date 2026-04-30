/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:16:50 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/29 14:52:53 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *)&str[i]);
		else
			i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	int	str[20] = {-49, 49, 1, -1, 0, -2, 2};
	int			c = -1;
	size_t		n = 47;
	char		*result = ft_memchr (str, c, n);

	printf ("%s\n", result);
	return (0);
}
*/