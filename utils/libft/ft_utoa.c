/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:06:01 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/16 20:06:03 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	utoa_size(unsigned long long n, int base)
{
	int	size;

	size = 0;
	while (n)
	{
		n = n / base;
		size++;
	}
	return (size);
}

static	void	fill_utoa(char *utoa, unsigned long n, int base)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (n)
	{
		r = n % base;
		if (r > 9)
			utoa[i++] = (r - 10) + 'a';
		else
			utoa[i++] = r + '0';
		n = n / base;
	}
	reverse(utoa, i);
}

char	*ft_utoa_base(unsigned long long n, int base)
{
	char				*utoa;
	unsigned long long	nbr;

	nbr = (unsigned long long)n;
	if (nbr == 0)
		return (ft_strdup("0"));
	utoa = (char *)ft_calloc((utoa_size(n, base) + 1), sizeof (char));
	if (!utoa)
		return (NULL);
	fill_utoa(utoa, nbr, base);
	return (utoa);
}
