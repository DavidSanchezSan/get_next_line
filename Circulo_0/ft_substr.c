/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:37:51 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/03 18:20:20 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Reserves and returns a substring of the string ‘s’.
// The substring starts from index ‘start’ and has a maximum length of ‘len’.

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*subs;
	const char	*to_copy;

	if (s == NULL || start >= ft_strlen(s) || len <= 0)
		return (ft_calloc(1, sizeof(char)));
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (len + start > ft_strlen(s))
		subs = malloc((len) * sizeof(char));
	else
		subs = malloc((len + 1) * sizeof(char));
	to_copy = &s[start];
	if (subs == NULL)
		return (NULL);
	ft_memcpy(subs, to_copy, len);
	subs[len] = '\0';
	return (subs);
}

// int	main(void)
// {
// 	const char *s = "hola";
// 	int start = 2;
// 	size_t len = 3;
// 	char *a = ft_substr(s, start, len);
// 	printf("String completo: %s\n", s);
// 	printf("Substring: %s", a);
// 	return (0);
// }