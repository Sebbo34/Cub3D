/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 12:59:24 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cross_event(t_window *window)
{
	printf("Cross clicked\n");
	mlx_loop_end(window->mlx_context);
	return (0);
}

int	key_event(int keycode, t_window *window)
{
	(void) keycode;
	printf("Key pressed\n");
	mlx_loop_end(window->mlx_context);
	return (0);
}

int main()
{
	t_window	window;

	// TODO: check null sur les deux
	window.mlx_context = mlx_init(); 
	window.window = mlx_new_window(window.mlx_context, 1000, 1000, "Hello");

	mlx_hook(window.window, DestroyNotify, 1L<<0, cross_event, &window);
	mlx_hook(window.window, KeyPress, KeyPressMask, key_event, &window);
	mlx_loop(window.mlx_context);
	
	mlx_destroy_window(window.mlx_context, window.window);
	mlx_destroy_display(window.mlx_context);
	free(window.mlx_context);
}