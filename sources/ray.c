/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 18:20:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ray_horizontal_dist(t_ray ray, uint32_t width)
{
	if (ray.direction_x > 0)
		return ((width - ray.start_x) / ray.direction_x);
	else
		return (ray.start_x / -ray.direction_x);
}

float	ray_vertical_dist(t_ray ray, uint32_t height)
{
	if (ray.direction_y > 0)
		return ((height - ray.start_y) / ray.direction_y);
	else
		return (ray.start_y / -ray.direction_y);
}

float	ft_float_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ray_intersect_rect(t_ray ray, uint32_t width, uint32_t height)
{
	if (ray.direction_x == 0)
		return (ray_vertical_dist(ray, height));
	if (ray.direction_y == 0)
		return (ray_horizontal_dist(ray, width));
	printf("Hor: %f\n", ray_horizontal_dist(ray, width));
	printf("Ver: %f\n", ray_vertical_dist(ray, height));
	return (ft_float_min(
		ray_horizontal_dist(ray, width),
		ray_vertical_dist(ray, height)
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
	max_distance = ray_intersect_rect(ray, image.width, image.height);
	printf("Distance: %f\n", max_distance);
	while (current_dist < max_distance - 20.0f)
	{
		project_ray(ray, current_dist, &pixel_x, &pixel_y);
		put_pixel(image, pixel_x, pixel_y, (t_color){.r = 255});
		current_dist += 1.0f;
	}
}