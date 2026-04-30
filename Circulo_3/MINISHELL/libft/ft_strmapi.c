/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:40:11 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/03 18:45:04 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	to_uppercase(unsigned int i, char c)
{
	(void)i; // No usamos el índice, así que evitamos el warning
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

int	main(void)
{
	char *str = "hola, mundo!";
	char *str_new;

	printf("Antes: %s\n", str);
	str_new = ft_strmapi(str, to_uppercase);
	printf("Después: %s\n", str_new);
	return (0);
}
*/