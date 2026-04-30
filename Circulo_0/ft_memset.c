/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:25:48 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:13:26 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that fills the first n bytes of the memory area pointed to
// by s with the constant byte c.

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		ptr[x] = c;
		x++;
	}
	return (s);
}
/*
int main(void)
{
    char str[50] = "Hola mundo";
    printf("Antes de memset: %s\n",str);
    ft_memset(str+1, 'A', 4);
    printf("Después de memset: %s\n", str);
    return (0);
}
*/