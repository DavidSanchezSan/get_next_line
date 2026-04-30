/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:00:49 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 15:56:45 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Removes one element of the list. Free the memory of the element
/// passed as parameter using the 'del' function, then free also the element.
/// The memory of 'next' must not be freed.
/// @param lst the element to free
/// @param del address of the function that can delete the element's content
/// @return none
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
/*
int	main(void)
{
	t_list	*node;

	node = ft_lstnew("Nodo Nuevo");
	printf("Nodo creado: %s\n", (char *)node->content);
	ft_lstdelone(node, free);
	printf("Nodo eliminado: %s\n",(char *)node->content);
	return (0);
}
*/