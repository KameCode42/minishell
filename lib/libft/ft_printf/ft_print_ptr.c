/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:16:33 by dle-fur           #+#    #+#             */
/*   Updated: 2024/11/07 17:18:53 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_p(size_t ptr, int *count)
{
	char	*base;
	char	str[25];
	int		i;

	base = "0123456789abcdef";
	i = 0;
	if (ptr == 0)
	{
		(*count) += write(1, "0x0", 3);
		return ;
	}
	(*count) += write(1, "0x", 2);
	while (ptr != 0)
	{
		str[i] = base[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		print_c(str[i], count);
	}
}
