/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/08 17:59:30 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <math.h>
# include "./../libft/includes/libft.h"
# include "./../mlx/mlx/mlx.h"
# include "map.h"

# define SIZE_BLOC	15
# define WIDTH	1280
# define HEIGHT	720
# define FOV			90.0f
# define WALL_HEIGHT	50.0f
# define NUM_WALLS		5

enum {
	CLOSE	= 17,
	ESC		= 65307,
	LEFT	= 65361,
	TOP		= 65362,
	RIGHT	= 65363,
	DOWN	= 65364,
	W		= 119,
	A		= 97,
	S		= 115,
	D		= 100,
};

typedef struct s_mlx
{
	void	*img;
	void	*addr;

	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_ray
{
	int		begin_vertical;
	int		end_vertical;

	int		begin_horizontal;
	int		end_horizontal;

	int		vertical_y;
	int		vertical_x;

	int		horizontal_y;
	int		horizontal_x;

	int		oppose; // vertical
	int		adjacent; // horizon
	int		hypothenuse;
	
}	t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;

	void		*img;
	void		*addr;

	void		*img_map;
	void		*img_addr;

	t_mlx		mlx;
	t_map		map;
	t_ray		ray;
	t_player	player;
}	t_data;

/*
	DIRECTORY:	./parsing
*/
//	parse.c

/*
	DIRECTORY:	./move
*/
//	movements.c
void BresenhamLine(t_mlx mlx, int x1, int y1, int x2, int y2);
void	move_vertical(t_data *data, int add);
void	move_horizontal(t_data *data, int add);

/*
	DIRECTORY:	./move
*/
//	movements.c
void	draw(t_data* data);
void	draw_map(t_data *data);

/*
	DIRECTORY:	./color
*/
//	color.c
int		set_rgb(int rgb[3]);

/*
	DIRECTORY: ./free
*/
//	free.c
void	free_cub3d(t_data *data);
/*
	DIRECTORY:	./
*/
//	main.c
void	mlx_put_pixel(t_mlx mlx, int x, int y, int color);
//	print.c
void	print_map(const t_data data);

#endif
