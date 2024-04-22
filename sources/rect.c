/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:39 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 13:16:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <math.h>

void	fill_rect(t_rect rect, t_image image, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			put_pixel(image, rect.start_x + j, rect.start_y + i, color);
			j++;
		}
		i++;
	}
}
