/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:41:14 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 11:44:28 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "image.h"
# include "scene.h"
# include "user_input.h"
# include <stdint.h>

typedef struct s_window
{
	void		*mlx_context;
	void		*window;
	t_image		background;
}	t_window;

typedef struct s_loop_context
{
	t_window	window;
	t_scene		*scene;
	t_keys		*keys;
}	t_loop_context;

bool	create_window(t_window *window, uint32_t width, uint32_t height);
bool	open_window(t_window *window, t_keys *keys);
void	update_window(t_window window);
void	close_window(t_window window);
void	destroy_window(t_window window);
int		cross_event(t_window *window);

#endif