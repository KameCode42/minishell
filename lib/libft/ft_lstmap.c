/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:43:15 by david             #+#    #+#             */
/*   Updated: 2024/10/11 14:38:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	void	*ptr;

	if (lst == NULL || !f || !del)
	{
		return (NULL);
	}
	new = NULL;
	while (lst != NULL)
	{
		ptr = f(lst->content);
		node = ft_lstnew(ptr);
		if (node == NULL)
		{
			del(ptr);
			ft_lstclear(&new, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}
