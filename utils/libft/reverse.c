/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:08:20 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/16 20:08:21 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	reverse(char *s, int len)
{
	int		start;
	int		end;
	char	t;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		t = s[start];
		s[start] = s[end];
		s[end] = t;
		end--;
		start++;
	}
}
