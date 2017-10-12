/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:17:10 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/12 14:10:10 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**make_board(char **board, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (j < size)
		{
			board[i][j] = '.';
			j++;
		}
		j = 0;
		i++;
	}
	return (board);
}

void	free_board(char **board, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(board[i]);
		i++;
	}
	free(board);
}

void	put_board(char **board, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (j < size)
		{
			ft_putchar(board[i][j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
}

void	allocate_mem(char ***board, int size)
{
	int i;

	i = 0;
	*board = (char**)malloc(sizeof(char*) * size);
	while (i < size)
	{
		(*board)[i] = (char *)malloc(sizeof(char) * size);
		i++;
	}
}

void	put_piece(t_tetro *piece, int x, int y, char **board)
{
	char id;

	id = piece->id;
	piece->onboard = 1;
	piece->previously_placed = 1;
	piece->current.x = x;
	piece->current.y = y;
	board[y + piece->offset[0].y][x + piece->offset[0].x] = id;
	board[y + piece->offset[1].y][x + piece->offset[1].x] = id;
	board[y + piece->offset[2].y][x + piece->offset[2].x] = id;
	board[y + piece->offset[3].y][x + piece->offset[3].x] = id;
}

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

int		can_put(t_tetro *piece, int x, int y, char **board, int size)
{
	int i;

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

int		place_innext_available(t_tetro *piece, char **board, int size)
{
	int x;
	int y;

	x = piece->current.x;
	y = piece->current.y;
	if ((x == 0) && (y == 0) && (piece->previously_placed == 1))
		x++;
	else if ((x != 0) || (y != 0))
	{
		if (x < size - 1)
			x++;
		else if (y < size - 1)
		{
			y++;
			x = 0;
		}
		else
			return (0);
	}
	while (y < size)
	{
		while (x < size)
		{
			if (can_put(piece, x, y, board, size))
			{
				put_piece(piece, x, y, board);
				return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
