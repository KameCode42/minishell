/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:54 by dle-fur           #+#    #+#             */
/*   Updated: 2024/10/11 13:20:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (*lst == NULL || del == NULL)
	{
		return ;
	}
	while (*lst != NULL)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = node;
	}
}
