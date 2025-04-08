/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:14:56 by dle-fur           #+#    #+#             */
/*   Updated: 2024/11/07 17:19:42 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(int c, int *count)
{
	(*count) += write(1, &c, 1);
}

void	print_s(char *str, int *count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		(*count) += write (1, "(null)", 6);
	}
	else
	{
		while (str[i] != '\0')
		{
			(*count) += write(1, &str[i], 1);
			i++;
		}
	}
}

void	print_hex(unsigned int nb, int maj, int *count)
{
	char	*base;

	if (maj == 1)
	{
		base = "0123456789ABCDEF";
	}
	else
	{
		base = "0123456789abcdef";
	}
	if (nb >= 16)
	{
		print_hex(nb / 16, maj, count);
		(*count) += write(1, &base[nb % 16], 1);
	}
	else
	{
		(*count) += write(1, &base[nb % 16], 1);
	}
}

void	print_n(int nb, int *count)
{
	char	*base;

	base = "0123456789";
	if (nb == -2147483648)
	{
		(*count) += write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		(*count) += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		print_n(nb / 10, count);
		(*count) += write(1, &base[nb % 10], 1);
	}
	else
	{
		(*count) += write(1, &base[nb % 10], 1);
	}
}

void	print_u(unsigned int nb, int *count)
{
	char	*base;

	base = "0123456789";
	if (nb >= 10)
	{
		print_u(nb / 10, count);
		(*count) += write(1, &base[nb % 10], 1);
	}
	else
	{
		(*count) += write(1, &base[nb % 10], 1);
	}
}
