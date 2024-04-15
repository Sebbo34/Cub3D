/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:25:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 16:34:41 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <stdint.h>

typedef	union 
{
	struct 
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
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

typedef struct s_window
{
	void		*mlx_context;
	void		*window;
	t_image		background;
}	t_window;

enum e_tile_kind
{
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
};

typedef struct s_map
{
	uint32_t			width;
	uint32_t			height;
	enum e_tile_kind	*tiles;
}	t_map;

typedef struct s_rect
{
	uint32_t	start_x;
	uint32_t	start_y;
	uint32_t	width;
	uint32_t	height;
}	t_rect;


t_map	init_map(void);
void	display_map(t_map map, t_image image);

void	put_pixel(t_image image, uint32_t x, uint32_t y, t_color color);

bool	create_image(void *mlx_context, t_image *image, uint32_t width,
			uint32_t height);
void	destroy_image(void *mlx_context, t_image image);
void	fill_rect(t_rect rect, t_image image, t_color color);

bool	create_window(t_window *window, uint32_t width, uint32_t height);
void	update_window(t_window window);
void	destroy_window(t_window window);

#endif