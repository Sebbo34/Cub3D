/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:41 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 13:05:25 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	move_player(int keycode, t_player *player)
{
	const float speed = 0.1f;

	if (keycode == XK_w)
	{
		player->x += player->direction_x * speed;
		player->y += player->direction_y * speed;
	}
	else if (keycode == XK_a)
	{
		player->x += player->direction_y * speed;
		player->y -= player->direction_x * speed;
	}
	else if (keycode == XK_s)
	{
		player->x -= player->direction_x * speed;
		player->y -= player->direction_y * speed;
	}
	else if (keycode == XK_d)
	{
		player->x -= player->direction_y * speed;
		player->y += player->direction_x * speed;
	}
	else
		turn_player(keycode, player);
	printf("Player pos: x: %f, y: %f\n", player->x, player->y);
}

void	turn_player(int keycode, t_player *player)
{
	const float angular_speed = 0.02f;
	float		rotation_cos;
	float		rotation_sin;
	float		old_direction_x;
	float		old_direction_y;

	rotation_cos = cos(angular_speed * 2 * M_PI);
	rotation_sin = sin(angular_speed * 2 * M_PI);
	old_direction_x = player->direction_x;
	old_direction_y = player->direction_y;
	if (keycode == XK_Right)
	{
		player->direction_x = old_direction_x * rotation_cos - old_direction_y * rotation_sin;
		player->direction_y = old_direction_x * rotation_sin + old_direction_y * rotation_cos;
	}
	else if (keycode == XK_Left)
	{
		player->direction_x = old_direction_x * rotation_cos + old_direction_y * rotation_sin;
		player->direction_y = - old_direction_x * rotation_sin + old_direction_y * rotation_cos;
	}
}
