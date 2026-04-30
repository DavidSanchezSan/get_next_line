/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:46:35 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 17:27:50 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Iterate over the list 'lst' and apply the function 'f' to the
/// content of all elements.
/// @param lst pointer address to one element of the list
/// @param f function to apply
/// @return none
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void	to_uppercase(void *content)
{
	char	*str;
	size_t	i;

	str = (char *)content;
	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
}

int	main(void)
{
	t_list	*first;
	t_list	*second;

	first = ft_lstnew(ft_strdup("hola"));
	second = ft_lstnew(ft_strdup("mundo"));
	first->next = second;
	second->next = NULL;
	printf("Result before lstmap: %s %s\n", (char *)first->content,
		(char *)second->content);
	ft_lstiter(first, to_uppercase);
	printf("Result after lstiter: %s %s\n", (char *)first->content,
		(char *)second->content);
	return (0);
}
*/