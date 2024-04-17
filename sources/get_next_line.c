/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:58:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/17 17:02:47 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_strnchr(char *str, size_t len, char c, size_t *pos)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (*pos = i, true);
		i++;
	}
	return (false);
}

bool	str_append(t_string *str, char *suffix, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = malloc(str->len + len + 1);
	if (!tmp)
		return (false);
	while (i < str->len)
	{
		tmp[i] = str->str[i];
		i++;
	}
	while (j < len)
	{
		tmp[i + j] = suffix[j];
		j++;
	}
	tmp[str->len + len] = '\0';
	free(str->str);
	str->str = tmp;
	str->len += len;
	return (true);
}

enum e_read_status	get_next_line(int fd, t_string *line)
{
	static t_buffer	buf;
	size_t			newline_pos;

	*line = (t_string){NULL, 0};
	while (true)
	{
		if (ft_strnchr(&buf.buffer[buf.pos], buf.len - buf.pos, '\n', &newline_pos))
		{
			if (!str_append(line, &buf.buffer[buf.pos], newline_pos))
				return (free(line->str), READ_ERROR);
			buf.pos += newline_pos + 1;
			return (READ_OK);
		}
		if (!str_append(line, &buf.buffer[buf.pos], buf.len - buf.pos))
			return (free(line->str), READ_ERROR);
		buf.pos = 0;
		buf.len = read(fd, buf.buffer, BUFFER_SIZE);
		if (buf.len < 0)
			return (free(line->str), READ_ERROR);
		if (buf.len == 0 && !line->len)
			return (READ_END);
		if (buf.len == 0)
			return (READ_OK);
	}
}