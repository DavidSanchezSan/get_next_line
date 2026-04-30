/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:58:21 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/07 15:36:55 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the last node of a list.

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int	main(void)
// {
// 	t_list *lista;
// 	t_list *a;
// 	t_list *b;
// 	t_list *c;
// 	t_list *d;

// 	lista = ft_lstnew("Comienzo");
// 	a = ft_lstnew("a");
// 	b = ft_lstnew("b");
// 	c = ft_lstnew("c");
// 	d = ft_lstnew("d");

// 	ft_lstadd_front(&d, c);
// 	ft_lstadd_front(&c, b);
// 	ft_lstadd_front(&b, a);
// 	ft_lstadd_front(&a, lista);

// 	t_list *last = ft_lstlast(lista);
// 	printf("%s", (char *)last->content);

// 	return(0);
// }