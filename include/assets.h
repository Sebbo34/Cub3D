/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:06:57 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 13:09:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H

# define ASSETS_H

# include <stdbool.h>
# include "image.h"

typedef struct s_incomplete_assets
{
	t_image			images[4];
	t_color			color[2];
	bool			is_found[6];
	unsigned int	count;
} t_incomplete_assets;

typedef struct s_assets
{
	t_image		no;
	t_image		so;
	t_image		we;
	t_image		ea;
	t_color		floor;
	t_color		ceiling;
}	t_assets;

bool		parse_assets(int fd, t_assets *assets, void *mlx_context);

#endif