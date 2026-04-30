/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:14:41 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:09:16 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that allocates memory for an array of nmemb elements of
// size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero.
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	total = nmemb * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total);
	return (ptr);
}
/*
int	main(void) {
	// Normal allocation (5 integers)
	size_t num_elements = 5;
	size_t size_of_element = sizeof(int);
	int *arr = (int *)calloc(num_elements, size_of_element);

	printf("Test 1: Normal Allocation\n");
	if (arr == NULL) {
		printf("Memory allocation failed!\n");
		return (1);
	}

	for (size_t i = 0; i < num_elements; i++) {
		printf("arr[%zu] = %d\n", i, arr[i]); 
			// Should print 0 for all elements
	}
	free(arr);

	return (0);
}
*/