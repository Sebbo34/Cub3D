/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 12:31:10 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	init_map(void)
{
	static enum e_tile_kind	tiles[] = {
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2,
		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2,
	};
	t_map					map;

	map.width = 11;
	map.height = 11;
	map.tiles = tiles;
	return (map);
}

void	display_map(t_map map, t_image image)
{
	t_rect		rect;
	unsigned	i;
	unsigned	j;
	
	rect.width = 100;
	rect.height = 100;
	i = 0;
	while (i < map.height)
	{
		rect.start_y = i * rect.height;
		j = 0;
		while (j < map.width)
		{
			rect.start_x = j * rect.width;
			if (map.tiles[i * map.width + j] == TILE_WALL)
				fill_rect(rect, image, (t_color){.hex = 0x303030});
			else
				fill_rect(rect, image, (t_color){.hex = 0});
			j++;
		}
		i++;
	}
}