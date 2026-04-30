/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egarcia2 <egarcia2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:59:22 by egarcia2          #+#    #+#             */
/*   Updated: 2025/02/10 17:19:54 by egarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Iterate over the list 'lst' and apply the function 'f' to the
/// content of each elements. Create a new list resulting of the successive
/// applications of 'f'. The function 'del' is used to destroy the content of
/// an element if necessary
/// @param lst pointer address to one element of the list
/// @param f address of function to apply
/// @param del address of the function that can delete an element's content
/// @return the new list or NULL if memory allocation fails
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*temp;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		new_content = f(lst->content);
		temp = ft_lstnew(new_content);
		if (!temp)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}
/*
void	*to_uppercase(void *content)
{
	char	*str;
	size_t	i;

	str = (char *)content;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

int	main(void)
{
	t_list *first;
	t_list *second;

	first = ft_lstnew(ft_strdup("hola"));
	second = ft_lstnew(ft_strdup("mundo"));

	first->next = second;
	second->next = NULL;

	printf("Result before lstmap: %s %s\n", (char *)first->content,
		(char *)second->content);

	t_list *new_list;
	new_list = ft_lstmap(first, to_uppercase, free);
	printf("Result after lstmap: %s %s\n", (char *)first->content,
		(char *)second->content);
	return (0);
}
*/