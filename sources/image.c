/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:22 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 15:50:15 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	create_image(
	void *mlx_context, t_image *image, uint32_t width, uint32_t height
) {
	int	bits_per_pixel;
	int	line_size;
	int	endian;

	image->mlx_image = mlx_new_image(mlx_context, width, height);
	if (!image->mlx_image)
		return (false);
	image->pixels = (t_color *) mlx_get_data_addr(image->mlx_image,
			&bits_per_pixel, &line_size, &endian);
	image->width = width;
	image->height = height;
	return (true);
}

void	destroy_image(void *mlx_context, t_image image)
{
	mlx_destroy_image(mlx_context, image.mlx_image);
}
