/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 11:33:24 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/13 18:10:29 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		count_connections(char *buf, int a)
{
	int i;

	i = 0;
	if ((a - 1) >= 0)
		if (buf[a - 1] == '#')
			i++;
	if (buf[a + 1] == '#')
		i++;
	if ((a - 5) >= 0)
		if (buf[a - 5] == '#')
			i++;
	if ((a + 5) <= 20)
		if (buf[a + 5] == '#')
			i++;
	return (i);
}

static int		is_solid(char *buf)
{
	int con[4];
	int j;
	int i;
	int total;

	i = 0;
	j = 0;
	while (i < 20)
	{
		if (((i + 1) % 5) == 0)
		{
			i++;
			continue;
		}
		if (buf[i] == '#')
		{
			con[j] = count_connections(buf, i);
			j++;
		}
		i++;
	}
	total = con[0] + con[1] + con[2] + con[3];
	if ((total != 6) && (total != 8))
		return (0);
	return (1);
}

static int		is_valid(char *buf)
{
	int size;
	int i;

	size = 0;
	i = 0;
	while (i < 20)
	{
		if (((i + 1) % 5) == 0)
		{
			if (buf[i] != '\n')
				return (1);
			i++;
			continue;
		}
		if ((buf[i] != '.') && (buf[i] != '#'))
			return (1);
		if (buf[i] == '#')
			size++;
		i++;
	}
	if (size != 4)
		return (1);
	if (is_solid(buf) != 1)
		return (1);
	return (0);
}

void			ft_err_exit(void)
{
	write(1, "error\n", 6);
	exit(1);
}

int				verify(char *filename)
{
	int		fd;
	int		tetr_count;
	char	buf[21];

	ft_bzero(buf, 21);
	tetr_count = 0;
	fd = open(filename, O_RDONLY);
	if ((fd < 0))
		ft_err_exit();
	is_file_empty(filename);
	is_newline_at_end(filename);
	while (read(fd, buf, 21) > 0)
	{
		if ((is_valid(buf) != 0) || (tetr_count > 26))
			ft_err_exit();
		tetr_count++;
		ft_bzero(buf, 21);
	}
	close(fd);
	return (tetr_count);
}
