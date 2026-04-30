/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:32:00 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/31 10:35:05 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
/*
int	main(void)
{
	size_t	num_elements = 5;
	size_t	size_of_element = sizeof(int);
	size_t	i;
	
	int *arr1 = calloc(num_elements, size_of_element);
	printf("Memory allocated\n");
	if(arr1 == NULL)
		printf("Memory allocation failed");
	i = 0;
	while (i < num_elements)
	{
		printf("%d\n", arr1[i]);
		i++;
	}
	return (0);
}
*/