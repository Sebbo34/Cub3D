/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 16:48:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>
#include <stdio.h>

float	ray_hit_vertical_lines(t_ray ray, int width)
{
	if (ray.direction_x == 0)
		return (INFINITY);
	if (ray.direction_x > 0)
		return ((width - ray.start_x) / ray.direction_x);
	else
		return (ray.start_x / -ray.direction_x);
}

float	ray_hit_horizontal_lines(t_ray ray, int height)
{
	if (ray.direction_y == 0)
		return (INFINITY);
	if (ray.direction_y > 0)
		return ((height - ray.start_y) / ray.direction_y);
	else
		return (ray.start_y / -ray.direction_y);
}

// Horizontal distance to vertical band
float	hor_dist_vert_band(t_ray ray, int width)
{
	if (ray.direction_x > 0 && ray.start_x < 0)
		return (-ray.start_x);
	if (ray.direction_x < 0 && ray.start_x >= width)
		return ((width - ray.start_x));
	return (INFINITY);
}

// Vertical distance to horizontal band
float	vert_dist_hor_band(t_ray ray, int height)
{
	if (ray.direction_y > 0 && ray.start_y < 0)
		return (-ray.start_y);
	if (ray.direction_y < 0 && ray.start_y >= height)
		return ((height - ray.start_y));
	return (INFINITY);
}

float	ray_hit_rect(t_ray ray, int width, int height)
{
	float	vert_dist;
	float	hor_dist;

	if (0 <= ray.start_x && ray.start_x < width
		&& 0 <= ray.start_y && ray.start_y < height)
		return (
			fmin(
				ray_hit_horizontal_lines(ray, width),
				ray_hit_vertical_lines(ray, height)
			)
		);
	else
	{
		hor_dist = hor_dist_vert_band(ray, width)
			* (ray.direction_y / ray.direction_x) + ray.start_y;
		if (0 <= hor_dist && hor_dist < height)
			return (hor_dist_vert_band(ray, width) / ray.direction_x);
		vert_dist = vert_dist_hor_band(ray, height)
			* (ray.direction_x / ray.direction_y) + ray.start_x;
		if (0 <= vert_dist && vert_dist < width)
			return (vert_dist_hor_band(ray, height) / ray.direction_y);
		return (INFINITY);
	}
}
