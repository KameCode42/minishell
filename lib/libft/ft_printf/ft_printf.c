/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:19:46 by dle-fur           #+#    #+#             */
/*   Updated: 2024/11/07 17:20:12 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_format(va_list args, const char format, int *count)
{
	if (format == '%')
		print_c('%', count);
	else if (format == 'c')
		print_c(va_arg(args, int), count);
	else if (format == 's')
		print_s(va_arg(args, char *), count);
	else if (format == 'x')
		print_hex(va_arg(args, unsigned int), 0, count);
	else if (format == 'X')
		print_hex(va_arg(args, unsigned int), 1, count);
	else if (format == 'd' || format == 'i')
		print_n(va_arg(args, int), count);
	else if (format == 'u')
		print_u(va_arg(args, unsigned int), count);
	else if (format == 'p')
		print_p(va_arg(args, size_t), count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	{
		while (format[i] != '\0')
		{
			if (format[i] == '%')
			{
				i++;
				check_format(args, format[i], &count);
			}
			else if (format[i] != '%')
			{
				count += write(1, &format[i], 1);
			}
			i++;
		}
	}
	va_end(args);
	return (count);
}
