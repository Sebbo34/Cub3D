/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:59:15 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:59:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include <stdbool.h>

typedef	union 
{
	struct 
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	uint32_t	hex;
} t_color;

typedef struct s_image
{
	void		*mlx_image;
	uint32_t	width;
	uint32_t	height;
	t_color		*pixels;
}	t_image;

typedef struct s_rect
{
	uint32_t	start_x;
	uint32_t	start_y;
	uint32_t	width;
	uint32_t	height;
}	t_rect;

void	put_pixel(t_image image, uint32_t x, uint32_t y, t_color color);

bool	create_image(void *mlx_context, t_image *image, uint32_t width,
			uint32_t height);
bool	load_image(void *mlx_context, t_image *image, char *path);
void	put_image(t_image dest, t_image src, t_rect zone);
void	destroy_image(void *mlx_context, t_image image);

void	fill_rect(t_rect rect, t_image image, t_color color);

#endif