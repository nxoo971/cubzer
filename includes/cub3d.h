/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/16 19:54:42 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <math.h>
# include "./../libft/includes/libft.h"
# include "./../mlx/mlx/mlx.h"
# include "map.h"

# define WIDTH	1280
# define HEIGHT	720

# define GAME_WIDTH		WIDTH - (WIDTH / 4)
# define GAME_HEIGHT	HEIGHT - (HEIGHT / 2)

# define ROTATION_SPEED	2. * (M_PI / 180.)
# define MOVE_SPEED	1.

# define FOV			90.0


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
	H		= 104,
	Y		= 121
};

enum {
	MLX_IMG_MAP,
	MLX_IMG_MINIMAP,
	MLX_IMG_GAME,
};

typedef struct s_mlx
{
	void	*img;
	void	*addr;
	int		index;

	int		bits_per_pixel[3];
	int		line_length[3];
	int		endian[3];
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	double	delta_y;
	double	delta_x;
	double	rotation_angle;
	double	view_direction;
	double	walk_direction;
}	t_player;

typedef struct s_ray
{
	int		begin_vertical;
	int		end_vertical;

	int		begin_horizontal;
	int		end_horizontal;

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
	void		*map_addr;

	void		*img_game;
	void		*game_addr;

	t_mlx		mlx;
	t_map		map;
	t_ray		ray;
	t_player	player;
}	t_data;

/*
	DIRECTORY:	./init
*/
//	init.c
int		init_mlx(t_data *data);
int		init_map(t_data *data);
int		init_minimap(t_data *data);
int		init_gameplay(t_data *data);

/*
	DIRECTORY:	./move
*/
//	movements.c
void	move_vertical(t_data *data, int add);
void	move_horizontal(t_data *data, int add);

/*
	DIRECTORY:	./draw
*/
//	draw.c

//	draw_ray.c
void	draw_game(t_data* data);
void	draw_gameplay(t_data *data, int add);
void	draw_ray(t_data *data);
void	draw_minimap(t_data *data);
//	bresenham.c
void	bresenham_line(t_mlx mlx, int x1, int y1, int x2, int y2);
void	bresenham_circle(t_mlx mlx, int xc, int yc, int r);

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
