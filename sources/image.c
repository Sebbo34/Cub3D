/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:22 by sbo               #+#    #+#             */
/*   Updated: 2024/04/23 19:21:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <mlx.h>

bool	create_image(
	void *mlx_context, t_image *image, int width, int height
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

bool	load_image(void *mlx_context, t_image *image, char *path)
{
	int	bits_per_pixel;
	int	line_size;
	int	endian;

	image->mlx_image = mlx_xpm_file_to_image(mlx_context, path,
			(int *) &image->width, (int *) &image->height);
	if (!image->mlx_image)
		return (false);
	image->pixels = (t_color *) mlx_get_data_addr(image->mlx_image,
			&bits_per_pixel, &line_size, &endian);
	return (true);
}

void	put_pixel(t_image image, int x, int y, t_color color)
{
	// if (0 <= x && x < image.width && 0 <= y && y < image.height)
		image.pixels[y * image.width + x] = color;
}

t_color	get_pixel(t_image image, int x, int y)
{
	// if (0 <= x && x < image.width && 0 <= y && y < image.height)
		return (image.pixels[y * image.width + x]);
	// return ((t_color){0});
}

void	destroy_image(void *mlx_context, t_image image)
{
	mlx_destroy_image(mlx_context, image.mlx_image);
}
