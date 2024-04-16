/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:02:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/16 15:32:08 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_key_event_context *context)
{
	if (keycode == XK_Escape)	
		return (mlx_loop_end(context->mlx_context));
	else if (keycode == XK_w)
		context->keys->w = true;
	else if (keycode == XK_a)
		context->keys->a = true;
	else if (keycode == XK_s)
		context->keys->s = true;
	else if (keycode == XK_d)
		context->keys->d = true;
	else if (keycode == XK_Left)
		context->keys->left = true;
	else if (keycode == XK_Right)
		context->keys->right = true;
	return (0);
}

int	key_release(int keycode, t_key_event_context *context)
{
	if (keycode == XK_w)
		context->keys->w = false;
	else if (keycode == XK_a)
		context->keys->a = false;
	else if (keycode == XK_s)
		context->keys->s = false;
	else if (keycode == XK_d)
		context->keys->d = false;
	else if (keycode == XK_Left)
		context->keys->left = false;
	else if (keycode == XK_Right)
		context->keys->right = false;
	return (0);
}