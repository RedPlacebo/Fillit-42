/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:17:13 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/13 12:43:06 by ikarishe         ###   ########.fr       */
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
//	printf("attempting to put piece %c, at position (x, y), (%d, %d)\n", id, x, y);
	piece->current.x = x;
	piece->current.y = y;
	board[y + piece->offset[0].y][x + piece->offset[0].x] = id;
	board[y + piece->offset[1].y][x + piece->offset[1].x] = id;
	board[y + piece->offset[2].y][x + piece->offset[2].x] = id;
	board[y + piece->offset[3].y][x + piece->offset[3].x] = id;
}
