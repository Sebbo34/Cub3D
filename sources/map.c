/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 19:31:54 by sbo              ###   ########.fr       */
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
void	ft_memcpy(void *dst, void *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
}

bool	ft_str_starts_with(t_string str, char *prefix)
{
	size_t	i;
	
	i = 0;
	while (prefix[i])
	{
		if (i >= str.len || prefix[i] != str.str[i])
			return (false);
		i++;
	}
	return (true);
}

bool	get_nonempty_line(int fd, t_string *line)
{
	while (get_next_line(fd, line) == READ_OK)
	{
		if (line->len != 0)
			return (true);
		free(line->str);
	}
	return (false);
}

bool	parse_direction(t_image *image, char *line, void *mlx_context)
{
	size_t	spaces;

	spaces = 0;
	while (line[spaces] == ' ')
		spaces++;
	return (spaces > 0 && load_image(mlx_context, image, &line[spaces]));
}

void free_incomplete_assets(t_incomplete_assets tmp, void *mlx_context)
{
	if (tmp.is_found[0])
		destroy_image(mlx_context, tmp.images[0]);
	if (tmp.is_found[1])
		destroy_image(mlx_context, tmp.images[1]);
	if (tmp.is_found[2])
		destroy_image(mlx_context, tmp.images[2]);
	if (tmp.is_found[3])
		destroy_image(mlx_context, tmp.images[3]);
}
bool	parse_assets(int fd, t_assets *assets, void *mlx_context)
{
	t_incomplete_assets tmp;
	char *const			identifier[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	t_string			line;
	size_t				i;
	
	tmp = (t_incomplete_assets){0};
	while (tmp.count < 4)
	{
		if (!get_nonempty_line(fd, &line))
			return (false);
		i = 0;
		while (i < 6)
		{
			if (ft_str_starts_with(line, identifier[i]))
			{
				if (i < 4)
				{
					if (tmp.is_found[i] || !parse_direction(&tmp.images[i], line.str + 2, mlx_context))
						return (free_incomplete_assets(tmp, mlx_context), free(line.str), false);
					tmp.count++;
					tmp.is_found[i] = true;
				}
			}
			i++;
		}
		free(line.str);
	}
	ft_memcpy(assets, &tmp, sizeof(t_assets));
	return (true);
} 

bool	load_scene(char *path, t_scene *scene, void *mlx_context)
{
	int		fd;

	(void) mlx_context;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	scene->map = init_map();
	scene->player = init_player();
	if (!parse_assets(fd, &scene->assets, mlx_context))
		return (close(fd), false);
	close (fd);
	return (true);
}

void	destroy_scene(t_scene scene, void *mlx_context)
{
	destroy_image(mlx_context, scene.assets.no);
	destroy_image(mlx_context, scene.assets.so);
	destroy_image(mlx_context, scene.assets.we);
	destroy_image(mlx_context, scene.assets.ea);
}
