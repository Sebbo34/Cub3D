/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 18:24:38 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int	main(void)
{
	t_ray		ray;
	float		dir_len;
	t_window	window;
	t_map		map;

	ray.start_x = 300.0f;
	ray.start_y = 200.0f;
	ray.direction_x = 60.0f;
	ray.direction_y = 0.0f;
	dir_len = sqrt(ray.direction_x * ray.direction_x + ray.direction_y * ray.direction_y);
	ray.direction_x /= dir_len;
	ray.direction_y /= dir_len;

	// TODO: check null sur les deux
	map = init_map();

	if (!create_window(&window, 100 * map.width, 100 * map.height))
		return (1);
	display_map(map, window.background);
	display_ray(ray, window.background);
	update_window(window);
	mlx_loop(window.mlx_context);
	destroy_window(window);
}
