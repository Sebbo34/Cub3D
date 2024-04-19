/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 16:57:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <mlx.h>

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
	player = &context->scene->player;
	move_player(*context->keys, player);
	display_map(context->scene->map, window.background, context->scene->assets);
	ray = (t_ray){player->x, player->y,
		player->direction_x, player->direction_y};
	fill_rect((t_rect){player->x * TILE_SIZE, player->y * TILE_SIZE, 5, 5},
				window.background, (t_color){.r = 255});
	if (0 <= player->x && player->x < context->scene->map.width
		&& 0 <= player->y && player->y < context->scene->map.height)
	{
		display_ray(ray, window.background);
		hit_type = ray_hit_walls(ray, context->scene->map, &hit_dist);
		if (hit_type == HIT_NS || hit_type == HIT_WE)
		{
			project_ray(ray, hit_dist, &hit_point_x, &hit_point_y);
			fill_rect((t_rect){hit_point_x * TILE_SIZE, hit_point_y * TILE_SIZE, 10, 10},
				window.background, (t_color){.b = 255});
		}
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
