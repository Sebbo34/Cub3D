/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 14:29:26 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

int	game_loop(t_loop_context *context)
{
	t_window				window;
	t_player				*player;
	t_ray					ray;
	float					hit_dist;
	enum e_hit_type			hit_type;
	float					hit_point_x;
	float					hit_point_y;

	window = context->window;
	player = context->player;
	move_player(*context->keys, player);
	display_map(context->map, window.background);
	ray = (t_ray){player->x, player->y,
		player->direction_x, player->direction_y};
	display_ray(ray, window.background);
	hit_type = ray_hit_walls(ray, context->map, &hit_dist);
	if (hit_type == HIT_NS || hit_type == HIT_WE)
	{
		project_ray(ray, hit_dist, &hit_point_x, &hit_point_y);
		fill_rect((t_rect){hit_point_x * TILE_SIZE, hit_point_y * TILE_SIZE, 10, 10},
			window.background, (t_color){.b = 255});
	}
	update_window(window);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window		window;
	t_map			map;
	t_player		player;
	t_keys			keys;

	keys = (t_keys){0};
	player.x = 2.5f;
	player.y = 2.5f;
	player.direction_x = 0.0f;
	player.direction_y = 1.0f;

	map = init_map();
	if (argc != 2 || !load_map(&map, argv[1]))
		return (1);
	if (!create_window(&window, TILE_SIZE * map.width, TILE_SIZE * map.height))
		return (1);
	mlx_hook(window.window, KeyPress, KeyPressMask, key_press, &(t_key_event_context){
		&keys, window.mlx_context});
	mlx_hook(window.window, KeyRelease, KeyReleaseMask, key_release, &(t_key_event_context){
		&keys, window.mlx_context});
	mlx_loop_hook(window.mlx_context, game_loop, &(t_loop_context){
		window, map, &player, &keys});
	mlx_loop(window.mlx_context);
	destroy_window(window);
}
