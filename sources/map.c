/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 14:47:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(void)
{
	static enum e_tile_kind	tiles[] = {
		2, 2, 2, 2, 2,
		2, 1, 1, 1, 2,
		2, 1, 1, 1, 2,
		2, 1, 1, 1, 2,
		2, 2, 2, 2, 2,
	};
	t_map					map;

	map.width = 5;
	map.height = 5;
	map.tiles = tiles;
	return (map);
}

void	display_map(t_map map)
{
	unsigned	i;
	unsigned	j;
	
	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			printf("%d ", map.tiles[i * map.width + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}