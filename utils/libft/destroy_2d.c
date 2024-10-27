/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:16:50 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/22 20:33:29 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	destroy_2d(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
