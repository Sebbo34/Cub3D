/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:55:32 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 12:21:43 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "user_input.h"

//						In turns/frame
# define TURNING_SPEED	0.01f
# define WALKING_SPEED	0.06f

typedef struct s_player
{
	float	x;
	float	y;
	float	direction_x;
	float	direction_y;
}	t_player;

void	move_player(t_keys keys, t_player *player);
void	turn_player(t_keys keys, t_player *player);

#endif