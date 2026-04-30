/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:32:52 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 15:56:26 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief add the 'new' node at the end of the list 'lst'
/// @param lst the pointer address to the first node in the list
/// @param  new the pointer address to the new node to add to the list
/// @return none
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

/*
int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*new;

	first = ft_lstnew("Nodo 1");
	second = ft_lstnew("Nodo 2");
	new = ft_lstnew("Nodo Nuevo");
	first->next = second;
	second->next = NULL;
	printf("Antes de add_back:\n");
	printf("first -> %s\n", (char *)first->content);
	printf("second -> %s\n", (char *)second->content);
	printf("second->next antes: %p\n", (void *)second->next);
	ft_lstadd_back(&first, new);
	printf("\nDespués de add_back:\n");
	printf("first -> %s\n", (char *)first->content);
	printf("second -> %s\n", (char *)second->content);
	printf("second->next ahora apunta a: %s\n", (char *)second->next->content);
	free(first);
	free(second);
	free(new);
	return (0);
}
*/