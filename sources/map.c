/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 18:17:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

bool	check_floor_closed(t_map map, int i, int j)
{
	if (i == map.height - 1 || map.tiles[(i + 1) * map.width + j] == TILE_VOID)
		return (false);
	if (i == 0 || map.tiles[(i - 1) * map.width + j] == TILE_VOID)
		return (false);
	if (j == 0 || map.tiles[i * map.width + j - 1] == TILE_VOID)
		return (false);
	if (j == map.width - 1 || map.tiles[i * map.width + j + 1] == TILE_VOID)
		return (false);
	return (true);
}

bool	check_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.tiles[i * map.width + j] == TILE_FLOOR)
			{
				if (!check_floor_closed(map, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_map(int fd, t_map *map, t_player *player)
{
	t_str_array		lines;

	if (!read_map_lines(fd, &lines))
		return (false);
	if (!search_player(lines, player))
		return (free_str_array(lines), false);
	map->width = get_max_len(&lines);
	map->height = lines.len;
	map->tiles = malloc(map->width * map->height * sizeof(t_tile));
	if (!map->tiles)
		return (free_str_array(lines), false);
	if (!parse_tiles(*map, lines))
		return (free(map->tiles), free_str_array(lines), false);
	free_str_array(lines);
	if (!check_map(*map))
		return (free(map->tiles), false);
	return (true);
}

void	display_map(t_map map, t_image image, t_assets assets)
{
	t_rect	rect;
	int		i;
	int		j;

	fill_rect((t_rect){0, 0, image.width, image.height}, image, (t_color){0});
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;
	i = 0;
	while (i < map.height)
	{
		rect.start_y = (image.height - TILE_SIZE * map.height) / 2 + i * rect.height;
		j = 0;
		while (j < map.width)
		{
			rect.start_x = (image.width - TILE_SIZE * map.width) / 2 + j * rect.width;
			if (map.tiles[i * map.width + j] == TILE_WALL)
				put_image(image, assets.no, rect);
			else if (map.tiles[i * map.width + j] == TILE_FLOOR)
				fill_rect(rect, image, assets.floor);
			else
				fill_rect(rect, image, assets.ceiling);
			j++;
		}
		i++;
	}
}
