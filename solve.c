/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:58:23 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/19 12:50:23 by ikarishe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		reset_all_following(t_tetro *pieces, int num_pieces,
		int tet_num)
{
	int i;

	i = tet_num + 1;
	while (i < num_pieces)
	{
		pieces[i].current.x = 0;
		pieces[i].current.y = 0;
		pieces[i].onboard = 0;
		pieces[i].previously_placed = 0;
		i++;
	}
}

void			are_we_done_yet(int *pieces_left, char **board, int *size,
		int *tet_num)
{
	*pieces_left = *pieces_left - 1;
	if (*pieces_left == 0)
	{
		put_board(board, *size);
		exit(0);
	}
	*tet_num = *tet_num + 1;
}

void			move_piece_zero(t_tetro *pieces, int *total_pieces,
		char **board, int *size)
{
	reset_tetros(pieces, *total_pieces);
	free_board(board, *size);
	solver(*total_pieces, pieces, (*size + 1));
}

void			remove_last(int *tet_num, t_tetro *pieces, char **board,
		int *total_pieces)
{
	*tet_num = *tet_num - 1;
	remove_piece(&pieces[*tet_num], pieces[*tet_num].current.x,
			pieces[*tet_num].current.y, board);
	reset_all_following(pieces, *total_pieces, *tet_num);
}

int				solver(int total_pieces, t_tetro *pieces, int size)
{
	int		tet_num;
	char	**board;
	int		pieces_left;

	pieces_left = total_pieces;
	tet_num = 0;
	allocate_mem(&board, size);
	board = make_board(board, size);
	while (1)
	{
		if (place_innext_available(&pieces[tet_num], board, size))
			are_we_done_yet(&pieces_left, board, &size, &tet_num);
		else
		{
			if (tet_num == 0)
				move_piece_zero(pieces, &total_pieces, board, &size);
			else
			{
				pieces_left++;
				remove_last(&tet_num, pieces, board, &total_pieces);
			}
		}
	}
	return (0);
}
