/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:51:07 by caqueiro          #+#    #+#             */
/*   Updated: 2023/11/08 16:30:55 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	size_t			p;
	int				f;
	unsigned char	uc;

	i = 0;
	p = 0;
	f = 0;
	uc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == uc)
		{
			p = i;
			f = 1;
		}
		i++;
	}
	if (!c)
		return ((char *)&s[i]);
	if (!f)
		return (NULL);
	return ((char *)&s[p]);
}

/*int	main(void)
{
	printf("%d\n", strrchr("oi,bb", 'b') == ft_strrchr("oi,bb", 'b'));
	printf("%d\n", strrchr("oi,bb", 0) == ft_strrchr("oi,bb", 0));
	printf("%d\n", strrchr("oi,bb", 'i') == ft_strrchr("oi,bb", 'i'));
}*/
