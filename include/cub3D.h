/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:25:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 19:01:16 by sbo              ###   ########.fr       */
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
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

//						8 KiB
# define BUFFER_SIZE	8192
# define TILE_SIZE		100

typedef	union 
{
	struct 
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	uint32_t	hex;
} t_color;

typedef struct s_image
{
	void		*mlx_image;
	uint32_t	width;
	uint32_t	height;
	t_color		*pixels;
}	t_image;

typedef struct s_window
{
	void		*mlx_context;
	void		*window;
	t_image		background;
}	t_window;

typedef struct s_ray
{
	float	start_x;
	float	start_y;
	float	direction_x;
	float	direction_y;
}	t_ray;

enum e_tile_kind
{
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
};

typedef struct s_map
{
	uint32_t			width;
	uint32_t			height;
	enum e_tile_kind	*tiles;
}	t_map;

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

typedef struct s_rect
{
	uint32_t	start_x;
	uint32_t	start_y;
	uint32_t	width;
	uint32_t	height;
}	t_rect;

typedef struct s_player
{
	float	x;
	float	y;
	float	direction_x;
	float	direction_y;
} t_player;

typedef struct s_keys
{
	bool	a;
	bool	d;
	bool	w;
	bool	s;
	bool	left;
	bool	right;
} t_keys;

typedef struct s_scene
{
	t_assets	assets;
	t_map		map;
	t_player	player;
}	t_scene;

typedef struct s_key_event_context
{
	t_keys	*keys;
	void	*mlx_context;
}	t_key_event_context;

typedef struct s_loop_context
{
	t_window	window;
	t_scene		*scene;
	t_keys		*keys;
}	t_loop_context;

enum e_hit_type
{
	HIT_NS,
	HIT_WE,
	HIT_NONE,
	HIT_IN_WALL,
};

typedef struct s_ray_progress
{
	float	vert_dist;
	float	hor_dist;
	float	max_dist;
}	t_ray_progress;

typedef	struct s_string
{
	char		*str;
	size_t		len;
} t_string;

typedef	struct s_buffer
{
	char		buffer[BUFFER_SIZE];
	size_t		pos;
	ssize_t		len;
} t_buffer;

enum e_read_status
{
	READ_OK,
	READ_END,
	READ_ERROR,
};

t_map				init_map(void);
bool				load_scene(char *path, t_scene *scene, void *mlx_context);
void				destroy_scene(t_scene scene, void *mlx_context);

void				display_map(t_map map, t_image image);

void				put_pixel(t_image image, uint32_t x, uint32_t y, t_color color);
void				fill_rect(t_rect rect, t_image image, t_color color);

bool				create_image(void *mlx_context, t_image *image, uint32_t width,
						uint32_t height);
bool				load_image(void *mlx_context, t_image *image, char *path);
void				destroy_image(void *mlx_context, t_image image);

bool				create_window(t_window *window, uint32_t width, uint32_t height);
bool				open_window(t_window *window, t_keys *keys);
void				update_window(t_window window);
void				close_window(t_window window);
void				destroy_window(t_window window);

float				ray_intersect_rect(t_ray ray, uint32_t width, uint32_t height);
float				ray_hit_vertical_lines(t_ray ray, uint32_t width);
float				ray_hit_horizontal_lines(t_ray ray, uint32_t height);
void				project_ray(t_ray ray, float dist, float *out_x, float *out_y);
void				display_ray(t_ray ray, t_image image);

enum e_hit_type		ray_hit_walls(t_ray ray, t_map map, float *hit_dist);

int					key_press(int keycode, t_key_event_context *context);
int					key_release(int keycode, t_key_event_context *context);

t_player			init_player(void);
void				move_player(t_keys keys, t_player *player);
void				turn_player(t_keys keys, t_player *player);

enum e_read_status	get_next_line(int fd, t_string *line);

#endif