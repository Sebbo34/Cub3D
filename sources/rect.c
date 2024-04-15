/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:39 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 16:03:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_image image, uint32_t x, uint32_t y, t_color color)
{
	if (x < image.width && y < image.height)
		image.pixels[y * image.width + x] = color;
}
