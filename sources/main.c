/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 12:50:40 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int	main(void)
{
	t_window		window;
	t_map			map;
	t_player		player;
	
	player.x = 2.5f;
	player.y = 2.5f;
	player.direction_x = 0.0f;
	player.direction_y = -1.0f;

	map = init_map();

	if (!create_window(&window, TILE_SIZE * map.width, TILE_SIZE * map.height))
		return (1);
	mlx_hook(window.window, KeyPress, KeyPressMask, key_event, &(t_key_event_context){
		window, map, &player
	});
	display_map(map, window.background);
	display_ray((t_ray){player.x, player.y,
		player.direction_x, player.direction_y}, window.background);
	update_window(window);
	mlx_loop(window.mlx_context);
	destroy_window(window);
}
