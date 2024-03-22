/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:32:32 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/18 20:56:07 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_print(char c, va_list args)
{
	if (c == 'c')
		return (write(1, &(char){va_arg(args, int)}, 1));
	else if (c == 's')
		return (ft_putstr((char *){va_arg(args, char *)}));
	else if (c == '%')
		return (write(1, "%", 1));
	else if (c == 'd' || c == 'i')
		return (print_itoa((signed int){va_arg(args, signed int)}, 10, 0));
	else if (c == 'u')
		return (print_utoa((unsigned int){va_arg(args, unsigned int)}, 10, 0));
	else if (c == 'x')
		return (print_utoa((unsigned int){va_arg(args, unsigned int)}, 16, 0));
	else if (c == 'X')
		return (print_utoa((unsigned int){va_arg(args, unsigned int)}, 16, 1));
	else if (c == 'p')
		return (print_pointer((void *){va_arg(args, void *)}, 16));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		buffer;

	buffer = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			buffer += handle_print(*(s + 1), args);
			s++;
		}
		else
			buffer += write(1, s, 1);
		s++;
	}
	va_end(args);
	return (buffer);
}

/*#include <stdio.h>
#include <limits.h>
int	main(void)
{
	printf(" %p %p ", LONG_MIN, LONG_MAX);
}*/
