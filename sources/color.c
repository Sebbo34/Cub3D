/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:47:19 by sbo               #+#    #+#             */
/*   Updated: 2024/04/22 12:17:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "parsing.h"

bool	parse_intensity(uint8_t *intensity, char **line)
{
	uint8_t	digit;
	uint8_t	value;

	if (!ft_str_match_digit(line, &value))
		return (false);
	if (!ft_str_match_digit(line, &digit))
		return (*intensity = value, true);
	value = value * 10 + digit;
	if (!ft_str_match_digit(line, &digit))
		return (*intensity = value, true);
	if (value > (255 - digit) / 10)
		return (false);
	*intensity = value * 10 + digit;
	return (true);
}

bool	parse_color(t_color *color, char *line)
{
	return (
		parse_intensity(&color->r, &line)
		&& ft_str_match(&line, ",")
		&& parse_intensity(&color->g, &line)
		&& ft_str_match(&line, ",")
		&& parse_intensity(&color->b, &line)
		&& *line == '\0'
	);
}
