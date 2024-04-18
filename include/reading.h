/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:56:52 by sbo               #+#    #+#             */
/*   Updated: 2024/04/18 12:15:32 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include <sys/types.h>
# include <stdbool.h>

//						8 KiB
# define BUFFER_SIZE	8192

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

enum e_read_status	get_next_line(int fd, t_string *line);
bool				get_nonempty_line(int fd, t_string *line);

#endif