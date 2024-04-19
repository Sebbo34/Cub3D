/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 14:19:06 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "scene.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

// t_map	init_map(void)
// {
// 	static t_tile	tiles[] = {
// 		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
// 		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
// 		2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2,
// 		2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
// 		2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2,
// 	};
// 	t_map			map;

// 	map.width = 11;
// 	map.height = 11;
// 	map.tiles = tiles;
// 	return (map);
// }

bool	read_map_lines(int fd, t_str_array *lines)
{
	enum e_read_status	status;
	t_str				line;

	*lines = (t_str_array){NULL, 0};
	if (!get_nonempty_line(fd, &line))
		return (false);
	status = READ_OK;
	while (status != READ_END)
	{
		if (!push_str(lines, line))
			return (free(line.str), free_str_array(*lines), false);
		status = get_next_line(fd, &line);
		if (status == READ_ERROR)
			return (free(line.str), free_str_array(*lines), false);
	}
	return (true);
}

uint32_t	get_map_width(t_str_array *lines)
{
	int			i;
	uint32_t	width;

	i = 0;
	width = 0;
	while (i < lines->len)
	{
		if ((uint32_t) lines->strs[i].len > width)
			width = lines->strs[i].len;
		i++;
	}
	return(width);
}

bool	char_to_tile(char c, t_tile *tile)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (*tile = TILE_FLOOR, true);
	if (c == '1')
		return (*tile = TILE_WALL, true);
	if (c == ' ')
		return (*tile = TILE_VOID, true);
	return (false);
}

bool	parse_tiles(t_map map, t_str_array lines)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < (uint32_t) lines.strs[i].len)
		{
			if (!char_to_tile(lines.strs[i].str[j], &map.tiles[i * map.width + j]))
			{
				printf("Parse tile failed: %c\n", lines.strs[i].str[j]);
				return (false);
			}
			j++;
		}
		while (j < map.width)
		{
			map.tiles[i * map.width + j] = TILE_VOID;
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_map(int fd, t_map *map)
{
	t_str_array		lines;

	if (!read_map_lines(fd, &lines))
		return (false);
	map->width = get_map_width(&lines);
	map->height = lines.len;
	map->tiles = malloc(map->width * map->height * sizeof(t_tile));
	if (!map->tiles)
		return (free_str_array(lines), false);
	
	if (!parse_tiles(*map, lines))
		return (free(map->tiles), free_str_array(lines), false);
	free_str_array(lines);
	return (true);
}

void	display_map(t_map map, t_image image, t_assets assets)
{
	t_rect		rect;
	unsigned	i;
	unsigned	j;
	
	rect.width = TILE_SIZE;
	rect.height = TILE_SIZE;
	i = 0;
	while (i < map.height && (i + 1) * rect.height < image.height)
	{
		rect.start_y = i * rect.height;
		j = 0;
		while (j < map.width && (j + 1) * rect.width < image.width)
		{
			rect.start_x = j * rect.width;
			if (map.tiles[i * map.width + j] == TILE_WALL)
				put_image(image, assets.no, rect);
			else
				fill_rect(rect, image, assets.floor);
			j++;
		}
		i++;
	}
}