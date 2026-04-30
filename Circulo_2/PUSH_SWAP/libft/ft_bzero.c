/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:31:30 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:08:39 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function that erases the data in the n bytes of the memory starting
at the location pointed to by s, by writing zeros (bytes containing '\0')
to that area. */

void	ft_bzero(void *s, size_t n)
{
	size_t			x;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		ptr[x] = '\0';
		x++;
	}
}

/*
int	main(void)
{
    char str[25] = "Hola mundo";
    printf("Antes de bzero: %s\n",str);
    ft_bzero(str, 2);
	printf("Despues de bzero: %s\n", str);
    printf("Despues de bzero a partir del tercer caracter: %s\n", str+2);
    return (0);
}
*/