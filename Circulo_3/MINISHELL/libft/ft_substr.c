/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:01:16 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 12:51:59 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	if (s == NULL || start >= ft_strlen(s) || len <= 0)
		return (ft_calloc(1, sizeof(char)));
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((start + len) > ft_strlen(s))
		str = malloc((len) * sizeof(char));
	else
		str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s[start] != '\0' && j < len)
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*
int	main(void)
{
	char const s[] = "hola";
	unsigned int start = 3;
	size_t len = 2;                
	printf("%s\n", ft_substr(s, start, len));
	return (0);
}
*/