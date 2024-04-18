/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:16:44 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "reading.h"
#include <fcntl.h>
#include <unistd.h>

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
