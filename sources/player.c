/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:41 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 15:22:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	move_player(t_keys keys, t_player *player)
{
	const float		speed = 0.01f;
	float			forward_movement;
	float			side_movement;

	forward_movement = keys.w - keys.s;
	side_movement = keys.d - keys.a;
	player->x += forward_movement * player->direction_x * speed;
	player->y += forward_movement * player->direction_y * speed;
	player->x += side_movement * -player->direction_y * speed;
	player->y += side_movement * player->direction_x * speed;
	turn_player(keys, player);
}

void	turn_player(t_keys keys, t_player *player)
{
	const float angular_speed = 0.002f;
	int			rotation_movement;
	float		rotation_cos;
	float		rotation_sin;
	float		old_direction_x;
	float		old_direction_y;

	rotation_movement = keys.right - keys.left;
	if (rotation_movement == 0)
		return ;
	rotation_cos = cos(angular_speed * 2 * M_PI);
	rotation_sin = sin(angular_speed * 2 * M_PI) * rotation_movement;
	old_direction_x = player->direction_x;
	old_direction_y = player->direction_y;
	player->direction_x = old_direction_x * rotation_cos - old_direction_y * rotation_sin;
	player->direction_y = old_direction_x * rotation_sin + old_direction_y * rotation_cos;
}
