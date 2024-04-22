/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 18:11:00 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <mlx.h>
#include <stdio.h>
#include <math.h>

int	game_loop(t_loop_context *context)
{
	t_window				window;
	t_player				*player;
	t_map					map;
	t_ray					ray;
	float					hit_dist;
	enum e_hit_type			hit_type;
	int						index;

	window = context->window;
	player = &context->scene->player;
	map = context->scene->map;
	move_player(*context->keys, player);
	display_map(map, window.background, context->scene->assets);
	fill_rect((t_rect){
		(window.background.width - TILE_SIZE * map.width) / 2 + player->x * TILE_SIZE - 2,
		(window.background.height - TILE_SIZE * map.height) / 2 + player->y * TILE_SIZE - 2,
		4, 4},
		window.background, (t_color){.hex = 0xFFFFFF});
	index = 0;
	while (index < window.background.width)
	{
		ray = ray_from_view_column(*player, (float) index / window.background.width);
		// ray = (t_ray){player->x, player->y,
		// 	player->direction_x, player->direction_y};
		hit_type = ray_hit_map(ray, map, &hit_dist);
		if (hit_type == HIT_IN_WALL)
			hit_dist = 0;
		if (hit_type == HIT_NONE)
			hit_dist = INFINITY;
		display_ray(offset_ray(ray,
			-((float) window.background.width / TILE_SIZE - map.width) / 2,
			-((float) window.background.height / TILE_SIZE - map.height) / 2),
			window.background, hit_dist);
		index++;
	}
	update_window(window);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window		window;
	t_scene			scene;
	t_keys			keys;

	keys = (t_keys){0};
	if (!create_window(&window, TILE_SIZE * 11, TILE_SIZE * 11))
		return (1);
	if (argc != 2 || !load_scene(argv[1], &scene, window.mlx_context))
		return (destroy_window(window), 1);
	if (!open_window(&window, &keys))
		return (destroy_window(window), 1);
	mlx_loop_hook(window.mlx_context, game_loop, &(t_loop_context){
		window, &scene, &keys});
	mlx_loop(window.mlx_context);
	close_window(window);
	destroy_scene(scene, window.mlx_context);
	destroy_window(window);
}
