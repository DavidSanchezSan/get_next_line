/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:33:35 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/01 17:31:32 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// To each character in the string ‘s’, apply the function ‘f’ giving as
// parameters the index of each character within ‘s’ and the character itself.
// It generates a new string with the result of the successive use of ‘f’.

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned int	x;
	char			*copy;

	x = 0;
	if (s == NULL)
		return (NULL);
	copy = ft_strdup(s);
	if (copy == NULL)
		return (NULL);
	while (copy[x] != '\0')
	{
		copy[x] = f(x, copy[x]);
		x++;
	}
	return (copy);
}

// char	ft_toupper_test(unsigned int c, char ch)
// {
// 	if (c % 2 == 0 && ch >= 'a' && ch <= 'z')
// 	{
// 		ch = ch - 32;
// 	}
// 	return(ch);
// }

// int	main(void)
// {
// 	char str[] = "hola mundo";
// 	char *copy = ft_strmapi(str, ft_toupper_test);
// 	printf("%s\n", str);
// 	printf("%s", copy);
// 	free(copy);
// 	return (0);
// }