/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 18:15:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>

void	project_ray(t_ray ray, float dist, float *out_x, float *out_y)
{
	*out_x = ray.start_x + ray.direction_x * dist;
	*out_y = ray.start_y + ray.direction_y * dist;
}

t_ray	offset_ray(t_ray ray, float offset_x, float offset_y)
{
	return ((t_ray){
		ray.start_x - offset_x,
		ray.start_y - offset_y,
		ray.direction_x,
		ray.direction_y,
	});
}

void	display_ray(t_ray ray, t_image image, float dist)
{
	float	max_distance;
	float	current_dist;
	float	pixel_x;
	float	pixel_y;

	current_dist = 0;
	max_distance = fmin(dist, ray_hit_rect(ray,
				image.width / TILE_SIZE, image.height / TILE_SIZE));
	if (max_distance == INFINITY)
		return ;
	while (current_dist < max_distance)
	{
		project_ray(ray, current_dist, &pixel_x, &pixel_y);
		put_pixel(image, pixel_x * TILE_SIZE, pixel_y * TILE_SIZE,
			(t_color){.r = 255});
		current_dist += 0.01f;
	}
}

// TODO: fix this for NS/WE from outside
enum e_hit_type	ray_hit_map(t_ray ray, t_map map, float *hit_dist)
{
	float			outside_dist;
	enum e_hit_type	hit_type;

	if (ray.start_x < 0 || map.width <= ray.start_x
		|| ray.start_y < 0 || map.height <= ray.start_y)
	{
		outside_dist = ray_hit_rect(ray, map.width, map.height);
		if (outside_dist == INFINITY)
			return (HIT_NONE);
		project_ray(ray, outside_dist, &ray.start_x, &ray.start_y);
		*hit_dist = 0;
		hit_type = ray_hit_walls(ray, map, hit_dist);
		if (hit_type == HIT_IN_WALL)
			hit_type = HIT_NS;
		*hit_dist += outside_dist;
		return (hit_type);
	}
	else
		return (ray_hit_walls(ray, map, hit_dist));
}