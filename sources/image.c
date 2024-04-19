/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:22 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 14:16:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <mlx.h>

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

void	put_pixel(t_image image, uint32_t x, uint32_t y, t_color color)
{
	if (x < image.width && y < image.height)
		image.pixels[y * image.width + x] = color;
}

void	put_image(t_image dest, t_image src, t_rect zone)
{
	uint32_t	i;
	uint32_t	j;
	t_color		pixel;

	i = 0;
	while (i < zone.height)
	{
		j = 0;
		while (j < zone.width)
		{
			pixel = src.pixels[i * src.height / zone.height * src.width
				+ j * src.width / zone.width];
			dest.pixels[(i + zone.start_y) * dest.width
				+ j + zone.start_x] = pixel;
			j++;
		}
		i++;
	}
}

void	destroy_image(void *mlx_context, t_image image)
{
	mlx_destroy_image(mlx_context, image.mlx_image);
}
