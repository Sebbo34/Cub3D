/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:51:48 by sbo               #+#    #+#             */
/*   Updated: 2024/04/19 11:54:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

bool	ft_str_match_digit(char **str, uint8_t *digit)
{
	if ('0' <= **str && **str <= '9')
	{
		*digit = **str - '0';
		(*str)++;
		return (true);
	}
	return (false);
}

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
