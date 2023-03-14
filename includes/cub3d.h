/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewancti <jewancti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:36:57 by jewancti          #+#    #+#             */
/*   Updated: 2023/03/14 23:21:36 by jewancti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <math.h>
# include "./../libft/includes/libft.h"
# include "./../mlx/mlx/mlx.h"
# include "./../mlx/mlx/mlx_int.h"
# include "map.h"

# define WIDTH	1280
# define HEIGHT	720

// MINI MAP
#define  PIXEL 15
#define LENMAP 20
#define OFFSET 3

// SPRITE
#define uDiv 1
#define vDiv 1
#define vMove 1.0
#define numSprites 2



typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}			t_sprite;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;



# define TEXTURE_SIZE		12
# define TEXTURE_WIDTH		64
# define TEXTURE_HEIGHT		64

# define ROTATION_SPEED	.045
# define MOVE_SPEED	0.16977777777

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
	char		p;
	double		x;
	double		y;
}	t_player;

typedef struct s_params
{
	double	dir_y;
	double	dir_x;
	int test;

	double	plane_y;
	double	plane_x;

	double	delta_y;
	double	delta_x;

	double	step;
	double	step_y;
	double	step_x;

	double	ray_y;
	double	ray_x;

	double	side_y;
	double	side_x;
	int		side;

	double	draw_start;
	double	draw_end;

	bool	re_buf;

	// sprite
	double sprite_x;
	double sprite_y;
	double invdet;
	double transform_x;
	double transform_y;
	int sprite_screen_x;
	int vmovescreen;
	int sprite_height;
	int draw_start_y;
	int draw_end_y;
	int sprite_width;
	int draw_start_x;
	int draw_end_x;
	int tex_x;
	int tex_y;
	int d;
	int color;
}	t_params;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int 		*texture[TEXTURE_SIZE];
	int			*buf[HEIGHT];
	int			zbuffer[WIDTH];

	double		*perpwalldist;

	void		*img;
	void		*xpm[TEXTURE_SIZE];
	void		*xpm_addr[TEXTURE_SIZE];
	void		*addr;

	void		*xpm[4];
	void		*xpm_addr[4];

	// sprite
	int		numsprite;
	int		*sprite_ord;
	double	*sprite_dis;

	int mouse;
	int mousebool;

	t_mlx		mlx;
	t_map		map;
	t_press		press;
	t_params	params;
	t_sprite	*sprite;
}	t_data;

/*
	DIRECTORY:	./init
*/
//	init.c
int		init_mlx(t_data *data);
int		init_map(t_data *data);
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
//	draw_ray.c
void	draw_gameplay(t_data *data);
//	texture.c
void	begin_textures(t_data *data, int x,
			double perp_wall_dist, int line_height);

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

void	mini_map(t_data *data);
void begin_sprite(t_data *data, t_player *player, t_params *params);



void load_texture(t_data *data);

// SPRITE
int	malloc_sprite(t_data *data);

// Mouse move
int   mouse_move(int sign_y, int sign_x, void *data);


#endif
