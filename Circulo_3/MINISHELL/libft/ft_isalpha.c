/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:21:51 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/05 15:32:18 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief checks if a character is a letter of the alphabet
/// @param c the character to evaluate
/// @return A non-zero value (true) if the character is a letter, 
/// or 0 (false) if it is not.
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

/*
int	main(void)
{
	int	c;

	c = '0';
	printf("%d\n", isalpha(c));
	printf("%d", ft_isalpha(c));
	return (0);
}
*/
