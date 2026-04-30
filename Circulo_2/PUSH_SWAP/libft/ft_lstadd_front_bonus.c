/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:33:24 by dasanche          #+#    #+#             */
/*   Updated: 2025/02/05 19:34:53 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds the new node to the beginning of the 'lst' list.

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
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

// 	printf("Lista: %p\n", lista);
// 	printf("a: %p\n", a);
// 	printf("b: %p\n", b);
// 	printf("c: %p\n", c);
// 	printf("d: %p\n", d);

// 	ft_lstadd_front(&lista, a);
// 	ft_lstadd_front(&lista, b);
// 	ft_lstadd_front(&lista, c);
// 	ft_lstadd_front(&lista, d);

// 	printf("%s -> %s -> %s -> %s -> %s -> %p\n",
// 		(char *) lista->content,
// 		(char *) lista->next->content,
// 		(char *) lista->next->next->content,
// 		(char *) lista->next->next->next->content,
// 		(char *) lista->next->next->next->next->content,
// 		lista->next->next->next->next->next
// 	);
// 	return(0);
// }