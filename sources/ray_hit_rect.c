/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 11:49:23 by sbo              ###   ########.fr       */
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

float	ray_hit_rect(t_ray ray, uint32_t width, uint32_t height)
{
	return (
		fmin(
			ray_hit_horizontal_lines(ray, width),
			ray_hit_vertical_lines(ray, height)
		)
	);
}
