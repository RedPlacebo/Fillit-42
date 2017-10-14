/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:58:23 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/13 17:45:31 by ekulyyev         ###   ########.fr       */
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
		{
			pieces_left--;
			if (pieces_left == 0)
			{
				put_board(board, size);
				return (0);
			}
			tet_num++;
		}
		else
		{
			if (tet_num == 0)
			{
				reset_tetros(pieces, total_pieces);
				free_board(board, size);
				if (solver(total_pieces, pieces, (size + 1)) == 0)
					return (0);
			}
			else
			{
				tet_num--;
				pieces_left++;
				remove_piece(&pieces[tet_num], pieces[tet_num].current.x,
							pieces[tet_num].current.y, board);
				reset_all_following(pieces, total_pieces, tet_num);
			}
		}
	}
	return (0);
}
