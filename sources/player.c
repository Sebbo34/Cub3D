/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:41 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:08:16 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>

t_player	init_player(void)
{
	t_player	player;

	player.x = 2.5f;
	player.y = 2.5f;
	player.direction_x = 0.0f;
	player.direction_y = 1.0f;
	return (player);
}

void	move_player(t_keys keys, t_player *player)
{
	const float		speed = 0.03f;
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
	const float angular_speed = 0.005f;
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
