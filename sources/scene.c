/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 14:20:01 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parsing.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

bool	load_scene(char *path, t_scene *scene, void *mlx_context)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	scene->player = init_player();
	if (!parse_assets(fd, &scene->assets, mlx_context))
		return (close(fd), false);
	if (!parse_map(fd, &scene->map))
		return (destroy_assets(scene->assets, mlx_context), close(fd), false);
	close (fd);
	return (true);
}

void	destroy_scene(t_scene scene, void *mlx_context)
{
	destroy_assets(scene.assets, mlx_context);
	free(scene.map.tiles);
}
