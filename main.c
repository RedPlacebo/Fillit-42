/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:40:49 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/13 15:44:02 by ikarishe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int		num_pieces;
	t_tetro	*pieces;

	num_pieces = 0;
	num_pieces = verify(argv[1]);
	pieces = (t_tetro *)malloc((
			(sizeof(int)) * 5 * 2 + sizeof(int) * 2 + sizeof(char) + 
			sizeof(t_location*)*4) * (num_pieces));
	pieces = make_tetros(argv[1], num_pieces, pieces);
	if (argc != 2)
	{
		write(2, "usage: fillit [filename]\n", 25);
		return (0);
	}
	if (num_pieces == 0)
		return (0);
	solver(num_pieces, pieces, 2);
	return (0);
}
