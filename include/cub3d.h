/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:25:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/15 14:45:54 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>

typedef struct s_window
{
	void	*mlx_context;
	void	*window;
}	t_window;

enum e_tile_kind
{
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
};

typedef struct s_map
{
	unsigned int		width;
	unsigned int		height;
	enum e_tile_kind	*tiles;
} t_map;

t_map	init_map(void);
void	display_map(t_map);

#endif