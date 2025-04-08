/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:58:17 by dle-fur           #+#    #+#             */
/*   Updated: 2024/10/02 11:54:14 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr_s;
	size_t	i;

	ptr_s = (char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr_s[i] == (char)c)
		{
			return ((void *)&ptr_s[i]);
		}
		i++;
	}
	return (NULL);
}
