/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:25:19 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/12 14:18:00 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				ft_putchar(char c)
{
	write(1, &c, 1);
}

static void			fill_tet(t_tetro *cur, char *buf, int id)
{
	int			i;
	t_location	xy;
	int			hashnum;

	i = -1;
	hashnum = -1;
	xy.x = 0;
	xy.y = 0;
	cur->onboard = 0;
	cur->previously_placed = 0;
	cur->current.x = 0;
	cur->current.y = 0;
	cur->id = id + 65;
	while (++i < 20)
	{
		if (((i + 1) % 5) == 0)
		{
			i++;
			xy.x = 0;
			xy.y++;
		}
		if (buf[i] == '#')
			cur->offset[++hashnum] = xy;
		xy.x++;
	}
}

void				put_tet_info(t_tetro piece)
{
	int i;

	i = 0;
	while (i < 4)
	{
		ft_putchar(piece.id);
		i++;
	}
}

static int			min(int a, int b, int c, int d)
{
	int res;

	res = 3;
	if (a < res)
		res = a;
	if (b < res)
		res = b;
	if (c < res)
		res = c;
	if (d < res)
		res = d;
	return (res);
}

static t_location	min_xy(t_tetro *piece)
{
	t_location shift;

	shift.x = min(piece->offset[0].x, piece->offset[1].x,
			piece->offset[2].x, piece->offset[3].x);
	shift.y = min(piece->offset[0].y, piece->offset[1].y,
			piece->offset[2].y, piece->offset[3].y);
	return (shift);
}

static void			topleft_shift(t_tetro *piece)
{
	int			i;
	t_location	xy_shift;

	i = 0;
	xy_shift = min_xy(piece);
	while (i < 4)
	{
		piece->offset[i].x = piece->offset[i].x - xy_shift.x;
		piece->offset[i].y = piece->offset[i].y - xy_shift.y;
		i++;
	}
}

t_tetro				*make_tetros(char *filename, int num_pieces,
					t_tetro *pieces)
{
	int		fd;
	char	buf[21];
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	while (read(fd, buf, 21) > 0)
	{
		fill_tet(&pieces[i], buf, i);
		i++;
	}
	i = 0;
	while (i < num_pieces)
	{
		topleft_shift(&pieces[i]);
		i++;
	}
	return (pieces);
}

void				reset_tetros(t_tetro *pieces, int num_pieces)
{
	int i;

	i = 0;
	while (i < num_pieces)
	{
		pieces[i].current.x = 0;
		pieces[i].current.y = 0;
		pieces[i].onboard = 0;
		pieces[i].previously_placed = 0;
		i++;
	}
}
