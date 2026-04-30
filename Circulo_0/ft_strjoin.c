/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:20:37 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/05 17:02:01 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Reserves with malloc and returns a new string,
// formed by the concatenation of ‘s1’ and ‘s2’.

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;

	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_string, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	new_string[ft_strlen(new_string)] = '\0';
	return (new_string);
}

// int	main(void)
// {
// 	const char *s1 = "lorem ipsum";
// 	const char *s2 = "dolor sit amet";
// 	char *a = ft_strjoin(s1, s2);
// 	printf("New string: %s", a);
// 	return (0);
// }