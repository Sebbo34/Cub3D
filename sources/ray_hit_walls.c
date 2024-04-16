/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:22 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 19:30:46 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_wall_ns(t_ray ray, float dist, t_map map)
{
	float	check_x;
	float	check_y;

	project_ray(ray, dist, &check_x, &check_y);
	if (ray.direction_y > 0)
		check_y += 0.5f;
	else
		check_y -= 0.5f;
	return (map.tiles[(int) check_y * map.width + (int) check_x] == TILE_WALL);
}

bool	check_wall_we(t_ray ray, float dist, t_map map)
{
	float	check_x;
	float	check_y;

	project_ray(ray, dist, &check_x, &check_y);
	printf("Projected point y: %f, x: %f]\n", check_y, check_x);
	if (ray.direction_x > 0)
		check_x += 0.5f;
	else
		check_x -= 0.5f;
	printf("Checking wall [%d][%d]\n", (int) check_y, (int) check_x);
	return (map.tiles[(int) check_y * map.width + (int) check_x] == TILE_WALL);
}

bool	ray_hit_walls(t_ray ray, t_map map, enum e_hit_direction *hit_dir, float *hit_dist)
{
	float	vert_dist;
	float	hor_dist;
	float	max_dist;

	max_dist = fmin(
		ray_hit_vertical_lines(ray, map.width),
		ray_hit_horizontal_lines(ray, map.height));
	vert_dist = ray_hit_vertical_lines((t_ray){
			ray.start_x - (int) ray.start_x, ray.start_y - (int) ray.start_y,
			ray.direction_x, ray.direction_y}, 1);
	hor_dist = ray_hit_horizontal_lines((t_ray){
			ray.start_x - (int) ray.start_x, ray.start_y - (int) ray.start_y,
			ray.direction_x, ray.direction_y}, 1);
	if (fabs(ray.direction_y) > fabs(ray.direction_x))
	{
		while (hor_dist < vert_dist && hor_dist < max_dist)
		{
			if (check_wall_ns(ray, hor_dist, map))
				return (*hit_dir = DIR_NS, *hit_dist = hor_dist, true);
			hor_dist += 1 / fabs(ray.direction_y);
		}
		while (vert_dist < max_dist)
		{
			if (check_wall_we(ray, vert_dist, map))
				return (*hit_dir = DIR_WE, *hit_dist = vert_dist, true);
			vert_dist += 1 / fabs(ray.direction_x);
			while (hor_dist < vert_dist && hor_dist < max_dist)
			{
				if (check_wall_ns(ray, hor_dist, map))
					return (*hit_dir = DIR_NS, *hit_dist = hor_dist, true);
				hor_dist += 1 / fabs(ray.direction_y);
			}
		}
	} else {
		while (vert_dist < hor_dist && vert_dist < max_dist)
		{
			if (check_wall_we(ray, vert_dist, map))
				return (*hit_dir = DIR_WE, *hit_dist = vert_dist, true);
			vert_dist += 1 / fabs(ray.direction_x);
		}
		while (hor_dist < max_dist)
		{
			if (check_wall_ns(ray, hor_dist, map))
				return (*hit_dir = DIR_NS, *hit_dist = hor_dist, true);
			hor_dist += 1 / fabs(ray.direction_y);
			while (vert_dist < hor_dist && vert_dist < max_dist)
			{
				if (check_wall_we(ray, vert_dist, map))
					return (*hit_dir = DIR_WE, *hit_dist = vert_dist, true);
				vert_dist += 1 / fabs(ray.direction_x);
			}
		}
	}
	return (false);
}
