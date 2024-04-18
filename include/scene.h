/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:47:56 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 13:09:09 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "map.h"
# include "assets.h"
# include "user_input.h"
# include <stdbool.h>

typedef struct s_player
{
	float	x;
	float	y;
	float	direction_x;
	float	direction_y;
} t_player;

typedef struct s_scene
{
	t_assets	assets;
	t_map		map;
	t_player	player;
}	t_scene;

bool		load_scene(char *path, t_scene *scene, void *mlx_context);
void		destroy_scene(t_scene scene, void *mlx_context);

t_player	init_player(void);
void		move_player(t_keys keys, t_player *player);
void		turn_player(t_keys keys, t_player *player);

#endif