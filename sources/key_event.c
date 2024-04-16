/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:02:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 12:40:31 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_event(int keycode, t_key_event_context *context)
{
	t_window	window;
	t_player	*player;

	window = context->window;
	player = context->player;
	if (keycode == XK_Escape)
		mlx_loop_end(window.mlx_context);
	else
		move_player(keycode, player);
	display_map(context->map, window.background);
	display_ray((t_ray){player->x, player->y,
		player->direction_x, player->direction_y}, window.background);
	update_window(window);
	return (0);
}
