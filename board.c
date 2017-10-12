/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:17:10 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/12 15:18:36 by ikarishe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	remove_piece(t_tetro *piece, int x, int y, char **board)
{
	piece->onboard = 0;
	board[y + piece->offset[0].y][x + piece->offset[0].x] = '.';
	board[y + piece->offset[1].y][x + piece->offset[1].x] = '.';
	board[y + piece->offset[2].y][x + piece->offset[2].x] = '.';
	board[y + piece->offset[3].y][x + piece->offset[3].x] = '.';
}

int		out_of_bounds(t_tetro *piece, int x, int y, int size)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if ((x + piece->offset[i].x >= size) ||
				(y + piece->offset[i].y >= size))
			return (1);
		i++;
	}
	return (0);
}

int		can_put(t_tetro *piece, t_location xy, char **board, int size)
{
	int i;
	int x;
	int y;

	x = xy.x;
	y = xy.y;
	i = 0;
	if (out_of_bounds(piece, x, y, size) == (1))
		return (0);
	while (i < 4)
	{
		if (board[y + piece->offset[i].y][x + piece->offset[i].x] != '.')
			return (0);
		i++;
	}
	return (1);
}

int		try_placing_it_everywhere(t_tetro *piece, char **board,
		int size, t_location *xy)
{
	while (xy->y < size)
	{
		while (xy->x < size)
		{
			if (can_put(piece, *xy, board, size))
			{
				put_piece(piece, xy->x, xy->y, board);
				return (1);
			}
			xy->x++;
		}
		xy->x = 0;
		xy->y++;
	}
	return (0);
}

int		place_innext_available(t_tetro *piece, char **board, int size)
{
	t_location xy;

	xy.x = piece->current.x;
	xy.y = piece->current.y;
	if ((xy.x == 0) && (xy.y == 0) && (piece->previously_placed == 1))
		xy.x++;
	else if ((xy.x != 0) || (xy.y != 0))
	{
		if (xy.x < size - 1)
			xy.x++;
		else if (xy.y < size - 1)
		{
			xy.y++;
			xy.x = 0;
		}
		else
			return (0);
	}
	return (try_placing_it_everywhere(piece, board, size, &xy));
}
