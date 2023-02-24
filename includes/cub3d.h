/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/02/24 05:22:11 by jewancti         ###   ########.fr       */
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

# define TEXTURE_SIZE		4
# define TEXTURE_WIDTH		64
# define TEXTURE_HEIGHT		64

# define GAME_WIDTH		WIDTH - (WIDTH / 4)
# define GAME_HEIGHT	HEIGHT - (HEIGHT / 2)

# define ROTATION_SPEED	.03
# define MOVE_SPEED	2 * (M_PI / 180.)

# define FOV			90.0

# define BLUE 0xF0000CC
# define BLACK 0xF000000
# define WHITE 0xFFFFFF
# define BEIGE 0xFE5A25E
# define RED 0xfD1111B

# define TPRESS_SIZE	7

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

enum {
	MLX_IMG_MAP,
	MLX_IMG_MINIMAP,
	MLX_IMG_GAME,
	MLX_IMG_SPRITES,
};

typedef struct s_mlx
{
	void	*img;
	void	*addr;
	int		index;

	int		bits_per_pixel[4];
	int		line_length[4];
	int		endian;
}	t_mlx;

typedef struct t_press
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	esc;
	int	left;
	int	right;
}	t_press;

typedef struct s_player
{
	double	x;
	double	y;
}	t_player;

typedef struct s_params
{
	double	dir_y;
	double	dir_x;

	double	plane_y;
	double	plane_x;

	double	delta_y;
	double	delta_x;

	double	step_y;
	double	step_x;

	double	ray_y;
	double	ray_x;

	double	side_y; // les caster en int pour un effet chelou
	double	side_x;
	int		side;

	double	draw_start;
	double	draw_end;

	bool	re_buf;
}	t_params;


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
	int 		**texture;
	int			**buf;

	void		*img;
	void		*xpm[4];
	void		*xpm_addr[4];
	void		*addr;

	void		*img_map;
	void		*map_addr;

	void		*img_game;
	void		*game_addr;

	t_mlx		mlx;
	t_map		map;
	t_ray		ray;
	t_player	player;
	t_press		press;
	t_params	params;
}	t_data;

/*
	DIRECTORY:	./init
*/
//	init.c
int		init_mlx(t_data *data);
int		init_map(t_data *data);
int		init_minimap(t_data *data);
int		init_gameplay(t_data *data);
//	init2.c
int		init_images(t_data *data);
int		init_buf_texture(t_data *data);
int		init_direction(t_params *params, const char spawn_direction);
int		init_plane(t_params *params);

/*
	DIRECTORY:	./key_hook
*/
//	key_hook.c
//int		key_hook(int keycode, t_data *data);
int		key_hook(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

/*
	DIRECTORY:	./move
*/
//	move.c
void	move_player(t_data *data, const int sign_y, const int sign_x);
void	move_player_side(t_data *data, const int sign_y, const int sign_x);
void	move_angle(t_data *data, const int sign);

/*
	DIRECTORY:	./draw
*/
//	draw.c

//	draw_ray.c
void	draw_game(t_data* data);
void	draw_gameplay(t_data *data);
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



void load_texture(t_data *data);


#endif
