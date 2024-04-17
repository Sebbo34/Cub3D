/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 18:03:05 by sbo              ###   ########.fr       */
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

// bool	ft_str_starts_with(t_string str, char *prefix)
// {
// 	size_t	i;
	
// 	i = 0;
// 	while (prefix[i])
// 	{
// 		if (i >= str.len || prefix[i] != str.str[i])
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// bool	get_nonempty_line(int fd, t_string *line)
// {
// 	while (get_next_line(fd, line) == READ_OK)
// 	{
// 		if (line->len != 0)
// 			return (true);
// 		free(line->str);
// 	}
// 	return (false);
// }
bool	load_map(char *path, t_map *map, t_assets *assets, void *mlx_context)
{
	int				fd;
	// t_string		line;
	// size_t			i;

	(void) map;
	(void) assets;
	(void) mlx_context;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	// if (!get_nonempty_line(fd, &line))
	// 	return (close(fd), false);
	// printf("Line: %s\n", line.str);
	// if (!ft_str_starts_with(line, "NO "))
	// 	return (free(line.str), close(fd), false);
	// i = 3;
	// while (i < line.len && line.str[i] == ' ')
	// 	i++;
	// if (!load_image(mlx_context, &assets->no, &line.str[i]))
	// 	return (free(line.str), close(fd), false);
	// destroy_image(mlx_context, assets->no);
	// free(line.str);
	close (fd);
	return (true);
}