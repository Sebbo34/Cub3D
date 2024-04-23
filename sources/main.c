/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/23 19:26:23 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "player.h"
#include <mlx.h>
#include <stdio.h>
#include <math.h>

void	draw_column(t_image_column dest, t_image_column src, float dest_height)
{
	t_color		pixel;
	const float	capped_dest_height = fmin(dest_height, dest.image.height);
	const float	const_a = (dest_height - capped_dest_height) / 2;
	const float	const_b = (dest.image.height - capped_dest_height) / 2;
	const float	const_c = src.image.height / dest_height;
	int			i;

	i = 0;
	while (i < capped_dest_height)
	{
		pixel = get_pixel(src.image, src.index,
				(i + const_a) * const_c);
		put_pixel(dest.image, dest.index,
			i + const_b, pixel);
		i++;
	}
}

float	get_wall_height(
	t_image background, t_player player, t_ray ray, float hit_dist
) {
	float	dist;

	dist = (player.direction_x * ray.direction_x
			+ player.direction_y * ray.direction_y) * hit_dist;
	return (background.height / (2 * tan(FOV * M_PI / 360)
			* background.height / background.width * dist));
}

t_image_column	get_src_column(
	t_assets assets, t_ray ray, float hit_type, float hit_dist
) {
	float	hit_x;
	float	hit_y;

	project_ray(ray, hit_dist, &hit_x, &hit_y);
	if (hit_type == HIT_WE && ray.direction_x > 0)
	{
		return ((t_image_column){assets.ea,
			(hit_y - (int)hit_y) * assets.ea.width});
	}
	else if (hit_type == HIT_WE && ray.direction_x < 0)
	{
		return ((t_image_column){assets.we,
			((int)hit_y + 1 - hit_y) * assets.we.width});
	}
	else if (hit_type == HIT_NS && ray.direction_y > 0)
	{
		return ((t_image_column){assets.so,
			((int)hit_x + 1 - hit_x) * assets.so.width});
	}
	else
	{
		return ((t_image_column){assets.no,
			(hit_x - (int)hit_x) * assets.no.width});
	}
}

void	display_column(t_scene scene, t_image background, int index)
{
	t_ray			ray;
	float			hit_dist;
	enum e_hit_type	hit_type;
	float			wall_height;
	t_image_column	src_column;

	ray = ray_from_view_column(scene.player, (float) index / background.width);
	hit_type = ray_hit_map(ray, scene.map, &hit_dist);
	wall_height = get_wall_height(background, scene.player, ray, hit_dist);
	if (hit_type == HIT_NS || hit_type == HIT_WE)
	{
		src_column = get_src_column(scene.assets, ray, hit_type, hit_dist);
		draw_column((t_image_column){background, index}, src_column,
			wall_height);
	}
}

int	game_loop(t_loop_context *context)
{
	t_image					background;
	int						index;

	background = context->window.background;
	move_player(*context->keys, &context->scene->player);
	fill_rect((t_rect){0, 0, background.width, background.height}, background,
		(t_color){0});
	index = 0;
	while (index < background.width)
	{
		display_column(*context->scene, background, index);
		index++;
	}
	update_window(context->window);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window		window;
	t_scene			scene;
	t_keys			keys;

	keys = (t_keys){0};
	if (!create_window(&window, WINDOW_WIDTH, WINDOW_HEIGHT))
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
