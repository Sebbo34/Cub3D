/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:09:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>

float	ray_hit_vertical_lines(t_ray ray, uint32_t width)
{
	if (ray.direction_x == 0)
		return (INFINITY);
	if (ray.direction_x > 0)
		return ((width - ray.start_x) / ray.direction_x);
	else
		return (ray.start_x / -ray.direction_x);
}

float	ray_hit_horizontal_lines(t_ray ray, uint32_t height)
{
	if (ray.direction_y == 0)
		return (INFINITY);
	if (ray.direction_y > 0)
		return ((height - ray.start_y) / ray.direction_y);
	else
		return (ray.start_y / -ray.direction_y);
}

float	ray_intersect_rect(t_ray ray, uint32_t width, uint32_t height)
{
	return (fmin(
		ray_hit_horizontal_lines(ray, width),
		ray_hit_vertical_lines(ray, height)
	));
}

void	project_ray(t_ray ray, float dist, float *out_x, float *out_y)
{
	*out_x = ray.start_x + ray.direction_x * dist;
	*out_y = ray.start_y + ray.direction_y * dist;
}

void	display_ray(t_ray ray, t_image image)
{
	float	max_distance;
	float	current_dist;
	float	pixel_x;
	float	pixel_y;

	current_dist = 0;
	max_distance = ray_intersect_rect(ray, image.width / TILE_SIZE, image.height / TILE_SIZE);
	while (current_dist < max_distance)
	{
		project_ray(ray, current_dist, &pixel_x, &pixel_y);
		put_pixel(image, pixel_x * TILE_SIZE, pixel_y * TILE_SIZE, (t_color){.r = 255});
		current_dist += 0.01f;
	}
}