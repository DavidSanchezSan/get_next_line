/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:19:56 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 15:16:11 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function function returns a pointer to a new string which is a duplicate of
// the string s.  Memory for the new string is obtained with malloc, and can
// be freed with free.

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s);
	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}
/*
int main() {
    const char *original = "Hello, world!";
    char *duplicate;

    // Create a duplicate of the original string using ft_strdup
    duplicate = ft_strdup(original);

    if (duplicate == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Print both the original and duplicated strings
    printf("Original: %s\n", original);
    printf("Duplicate: %s\n", duplicate);

    // Free the allocated memory for the duplicate string
    free(duplicate);

    return 0;
}
*/