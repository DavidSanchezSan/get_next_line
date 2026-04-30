/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:30 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/04 15:59:51 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that copies n bytes from memory area src to memory area dest.
// The memory areas must not overlap.

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			x;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	x = 0;
	if (src == dest)
		return (dest);
	while (x < n)
	{
		ptr_dest[x] = ptr_src[x];
		x++;
	}
	return (ptr_dest);
}

// int main()
// {
//     char str1[] = "";
//     char str2[] = "";

//     printf("Antes de memcpy: %s\n",str1);
// 	ft_memcpy(str1, str2, 3);
//     printf("Despues de memcpy: %s\n",str1);

//     return 0;
// }
// Control line: if (src == dest) {return (dest)} Done because of Paco.
