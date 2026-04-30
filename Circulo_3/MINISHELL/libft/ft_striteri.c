/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:24:27 by egarcia2          #+#    #+#             */
/*   Updated: 2025/01/31 19:54:51 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// void	to_uppercase(unsigned int i, char *c)
// {
// 	(void)i; // No usamos el índice, así que evitamos el warning
// 	if (*c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// }

// int	main(void)
// {
// 	char str[] = "hola, mundo!";

// 	printf("Antes: %s\n", str);
// 	ft_striteri(str, to_uppercase);
// 	printf("Después: %s\n", str);

// 	return (0);
// }