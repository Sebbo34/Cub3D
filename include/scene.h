/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:47:56 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:17:18 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "map.h"
# include "image.h"
# include "user_input.h"
# include <stdbool.h>

typedef struct s_incomplete_assets
{
	t_image			images[4];
	t_color			color[2];
	bool			is_found[6];
	unsigned int	count;
} t_incomplete_assets;

typedef struct s_assets
{
	t_image		no;
	t_image		so;
	t_image		we;
	t_image		ea;
	t_color		floor;
	t_color		ceiling;
}	t_assets;

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

bool		parse_assets(int fd, t_assets *assets, void *mlx_context);

t_player	init_player(void);
void		move_player(t_keys keys, t_player *player);
void		turn_player(t_keys keys, t_player *player);

#endif