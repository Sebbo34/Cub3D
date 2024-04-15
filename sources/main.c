/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 16:37:25 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(void)
{
	t_window	window;
	t_map		map;

	// TODO: check null sur les deux
	map = init_map();

	if (!create_window(&window, 100 * map.width, 100 * map.height))
		return (1);
	display_map(map, window.background);
	update_window(window);
	mlx_loop(window.mlx_context);
	destroy_window(window);
}
