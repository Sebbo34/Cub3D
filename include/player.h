/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:55:32 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 17:57:57 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

# include "user_input.h"

typedef struct s_player
{
	float	x;
	float	y;
	float	direction_x;
	float	direction_y;
} t_player;

void		move_player(t_keys keys, t_player *player);
void		turn_player(t_keys keys, t_player *player);

#endif