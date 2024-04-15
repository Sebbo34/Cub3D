/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:30:00 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 16:43:42 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

bool	create_window(t_window *window, uint32_t width, uint32_t height)
{
	window->mlx_context = mlx_init();
	if (!window->mlx_context)
		return (false);
	window->window = mlx_new_window(window->mlx_context, width, height,
		"Cub3D");
	if (!window->window)
	{
		mlx_destroy_display(window->mlx_context);
		free(window->mlx_context);
		return (false);
	}
	if (!create_image(window->mlx_context, &window->background, width, height))
	{
		mlx_destroy_window(window->mlx_context, window->window);
		mlx_destroy_display(window->mlx_context);
		free(window->mlx_context);
		return (false);
	}
	mlx_hook(window->window, DestroyNotify, 1L << 0, cross_event, window);
	mlx_hook(window->window, KeyPress, KeyPressMask, key_event, window);
	return (true);
}

void	update_window(t_window window)
{
	mlx_put_image_to_window(window.mlx_context, window.window,
		window.background.mlx_image, 0, 0);
}

void	destroy_window(t_window window)
{
	destroy_image(window.mlx_context, window.background);
	mlx_destroy_window(window.mlx_context, window.window);
	mlx_destroy_display(window.mlx_context);
	free(window.mlx_context);
}

