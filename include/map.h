/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:51:18 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 14:12:01 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "image.h"
# include "assets.h"
# include <stdint.h>

# define TILE_SIZE		100

enum e_hit_type
{
	HIT_NS,
	HIT_WE,
	HIT_NONE,
	HIT_IN_WALL,
};

enum e_tile_line_status
{
	TILE_LINE_OK,
	TILE_LINE_ERROR,
	TILE_LINE_NO_FLOOR,
};

typedef struct s_ray
{
	float	start_x;
	float	start_y;
	float	direction_x;
	float	direction_y;
}	t_ray;

typedef struct s_ray_progress
{
	float	vert_dist;
	float	hor_dist;
	float	max_dist;
}	t_ray_progress;

typedef enum e_tile_kind
{
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
}	t_tile;

typedef struct s_map
{
	uint32_t			width;
	uint32_t			height;
	t_tile				*tiles;
}	t_map;

// t_map			init_map(void);
bool			parse_map(int fd, t_map *map);
void			display_map(t_map map, t_image image, t_assets assets);

float			ray_intersect_rect(t_ray ray, uint32_t width, uint32_t height);
float			ray_hit_vertical_lines(t_ray ray, uint32_t width);
float			ray_hit_horizontal_lines(t_ray ray, uint32_t height);
void			project_ray(t_ray ray, float dist, float *out_x, float *out_y);
void			display_ray(t_ray ray, t_image image);

enum e_hit_type	ray_hit_walls(t_ray ray, t_map map, float *hit_dist);


#endif