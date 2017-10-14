/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulyyev <ekulyyev@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 18:05:05 by ekulyyev          #+#    #+#             */
/*   Updated: 2017/10/13 18:06:48 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			is_file_empty(char *filename)
{
	int		fd;
	char	buf[1];

	fd = open(filename, O_RDONLY);
	if (!(read(fd, buf, 1)))
	{
		write(1, "error\n", 6);
		exit(1);
	}
	close(fd);
}

void			ft_bzero(void *str, size_t n)
{
	char *s;

	s = str;
	while (n > 0)
	{
		*s++ = 0;
		n--;
	}
}

void			is_newline_at_end(char *filename)
{
	char	buf[26 * 21 + 1];
	int		i;
	int		fd;

	i = 0;
	ft_bzero(buf, 26 * 21 + 1);
	fd = open(filename, O_RDONLY);
	while (read(fd, &buf[i], 1) > 0)
		i++;
	if (buf[i - 2] == '\n')
	{
		write(1, "error\n", 6);
		exit(1);
	}
}
