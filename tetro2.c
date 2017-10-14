/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetro2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulyyev <ekulyyev@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 17:55:28 by ekulyyev          #+#    #+#             */
/*   Updated: 2017/10/13 18:03:50 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				ft_putchar(char c)
{
	write(1, &c, 1);
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
