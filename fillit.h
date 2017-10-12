/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarishe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:23:47 by ikarishe          #+#    #+#             */
/*   Updated: 2017/10/12 14:15:59 by ekulyyev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct
{
	int				x;
	int				y;
}					t_location;

typedef	struct
{
	char			id;
	int				onboard;
	int				previously_placed;
	t_location		current;
	t_location		offset[4];
}					t_tetro;

static void			fill_tet(t_tetro *cur, char *buf, int id);
void				put_tet_info(t_tetro piece);
static t_location	min_xy(t_tetro *piece);
static void			topleft_shift(t_tetro *piece);
t_tetro				*make_tetros(char *filename, int num_pieces,
					t_tetro *pieces);
static int			count_connections(char *buf, int a);
static int			is_solid(char *buf);
static int			is_valid(char *buf);
int					verify(char *filename);
char				**make_board(char **board, int size);
void				free_board(char **board, int size);
void				put_board(char **board, int size);
void				allocate_mem(char ***board, int size);
void				ft_putchar(char c);
void				put_piece(t_tetro *piece, int x, int y, char **board);
int					can_put(t_tetro *piece, int x, int y, char **board,
					int size);
int					out_of_bounds(t_tetro *piece, int x, int y, int size);
void				remove_piece(t_tetro *piece, int x, int y, char **board);
int					solver(int total_pieces, t_tetro *pieces, int size);
int					place_innext_available(t_tetro *piece, char **board,
					int size);
void				reset_tetros(t_tetro *pieces, int num_pieces);

#endif
