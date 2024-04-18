/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 15:51:44 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets.h"
#include "reading.h"
#include <stdlib.h>
#include <stdio.h>

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

bool	ft_str_match(char **str, char *prefix)
{
	size_t	i;
	
	i = 0;
	while (prefix[i])
	{
		if (prefix[i] != (*str)[i])
			return (false);
		i++;
	}
	(*str) += i;
	return (true);
}

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

bool	ft_str_match_digit(char **str)
{
	if ('0' <= **str && **str <= '9')
	{
		(*str)++;
		return (true);
	}
	return (false);
}

bool	parse_intensity(uint8_t *intensity, char **line)
{
	uint8_t	value;

	if (!ft_str_match_digit(line))
		return (false);
	value = **line - '0';
	if (!ft_str_match_digit(line))
		return (*intensity = value, true);
	value = value * 10 + **line - '0';
	if (!ft_str_match_digit(line))
		return (*intensity = value, true);
	if (value > (255 - (**line - '0')) / 10)
		return (false);
	value = value * 10 + **line - '0';
	*intensity = value;
	return (true);
}

bool	parse_color(t_color *color, char *line)
{
	return (
		parse_intensity(&color->r, &line)
		&& ft_str_match(&line, ",")
		&& parse_intensity(&color->g, &line)
		&& ft_str_match(&line, ",")
		&& parse_intensity(&color->g, &line)
		&& *line == '\0'
	);
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

bool	match_identifier(char **line, int *index)
{
	char *const	identifier[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_str_match(line, identifier[i]))
		{
			if (!ft_str_match(line, " "))
				return (false);
			skip_spaces(line);
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	parse_asset(char *line, t_incomplete_assets *assets, void *mlx_context)
{
	int	i;

	if (!match_identifier(&line, &i))
		return (false);
	if (assets->is_found[i])
		return (false);
	if (i < 4)
	{
		if (!load_image(mlx_context, &assets->images[i], line))
			return (false);
	}
	else
	{
		if (!parse_color(&assets->colors[i - 4], line))
			return (false);
	}
	assets->count++;
	assets->is_found[i] = true;
	return (false);
}

bool	parse_assets(int fd, t_assets *assets, void *mlx_context)
{
	t_incomplete_assets tmp_assets;
	t_string			line;
	
	tmp_assets = (t_incomplete_assets){0};
	while (tmp_assets.count < 6)
	{
		if (!get_nonempty_line(fd, &line))
			return (free_incomplete_assets(tmp_assets, mlx_context), false);
		if (!parse_asset(line.str, &tmp_assets, mlx_context))
			return (free_incomplete_assets(tmp_assets, mlx_context), free(line.str), false);
		free(line.str);
	}
	ft_memcpy(assets, &tmp_assets, sizeof(t_assets));
	return (true);
} 
