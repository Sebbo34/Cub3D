/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 16:22:51 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cross_event(t_window *window)
{
	mlx_loop_end(window->mlx_context);
	return (0);
}

int	key_event(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
		mlx_loop_end(window->mlx_context);
	return (0);
}

int	main(void)
{
	t_window	window;
	t_map		map;
	t_rect		rect = {
		50, 200, 100, 100
	};

	// TODO: check null sur les deux
	map = init_map();

	window.mlx_context = mlx_init();
	window.window = mlx_new_window(window.mlx_context, map.width * 100, map.height * 100, "Hello");
	create_image(window.mlx_context, &window.background, map.width * 100, map.height * 100);
	display_map(map, window.background);
	fill_rect(rect, window.background, (t_color){.hex = 0x00FF0000});
	mlx_put_image_to_window(window.mlx_context, window.window, window.background.mlx_image, 0, 0);
	mlx_hook(window.window, DestroyNotify, 1L << 0, cross_event, &window);
	mlx_hook(window.window, KeyPress, KeyPressMask, key_event, &window);
	mlx_loop(window.mlx_context);
	destroy_image(window.mlx_context, window.background);
	mlx_destroy_window(window.mlx_context, window.window);
	mlx_destroy_display(window.mlx_context);
	free(window.mlx_context);
}
