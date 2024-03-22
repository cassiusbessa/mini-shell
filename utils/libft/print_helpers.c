/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:37:25 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/16 22:37:27 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*s)
	{
		write(1, s, 1);
		s++;
		count++;
	}
	return (count);
}

int	prefix_pointer(void)
{
	return (write(1, "0x", 2));
}

int	print_itoa(long n, int base, int upper)
{
	int		buffer;
	char	*itoa;
	int		i;

	itoa = ft_itoa_base(n, base);
	i = 0;
	if (upper)
		while (itoa[i++])
			itoa[i] = ft_toupper(itoa[i]);
	buffer = ft_putstr(itoa);
	free(itoa);
	return (buffer);
}

int	print_utoa(unsigned long long n, int base, int upper)
{
	int		buffer;
	char	*utoa;
	int		i;

	utoa = ft_utoa_base(n, base);
	i = 0;
	if (upper)
	{
		while (utoa[i])
		{
			utoa[i] = ft_toupper(utoa[i]);
			i++;
		}
	}
	buffer = ft_putstr(utoa);
	free(utoa);
	return (buffer);
}

int	print_pointer(void *p, int base)
{
	int					buffer;
	unsigned long long	n;

	n = (unsigned long long)p;
	if (!n)
		return (write(1, "(nil)", 5));
	buffer = 0;
	buffer += prefix_pointer();
	buffer += print_utoa(n, base, 0);
	return (buffer);
}
