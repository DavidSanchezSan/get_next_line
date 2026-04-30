/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:24:55 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 15:32:59 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/// @brief Creates a new node using malloc(3). The member variable 'content' 
/// is initialized with the value of the 'content' parameter. The 'next' 
/// variable is initialized with NULL.
/// @param content The content of the new element
/// @return the new node
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int	main(void)
{
	char	*str;
	t_list	*node;

	str = "Hola Mundo";
	node = ft_lstnew((void *)str);
	printf("Contenido del nodo: %s\n", (char *)node->content);
	free(node);
	return (0);
}
*/